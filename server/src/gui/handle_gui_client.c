/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** handle_gui_client
*/

#include <string.h>
#include "server.h"
#include "gui/tab.h"

static gui_command_t *get_gui_command(const char *command_name)
{
    if (command_name == NULL)
        return NULL;
    for (size_t i = 0; i < NB_GUI_COMMANDS; i++) {
        if (strcmp(command_name, GUI_COMMANDS[i].name) == 0)
            return GUI_COMMANDS[i].command;
    }
    return NULL;
}

int handle_gui(struct client_entry *client, struct server *server, char *line)
{
    char *command[4];
    gui_command_t *command_func = NULL;

    command[0] = strtok(line, " \t");
    for (int i = 1; i < 4; i++)
        command[i] = strtok(NULL, " \t");
    command_func = get_gui_command(command[0]);
    if (command_func == NULL) {
        add_to_buffer(&client->buf_to_send, "suc\n", 4);
        return EXIT_SUCCESS;
    }
    if (command_func(command, server, client) == EXIT_FAILURE)
        add_to_buffer(&client->buf_to_send, "sbp\n", 4);
    return EXIT_SUCCESS;
}
