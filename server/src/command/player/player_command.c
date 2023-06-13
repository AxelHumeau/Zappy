/*
** EPITECH PROJECT, 2023
** player_command.c
** File description:
** player_command
*/

#include <string.h>
#include "macro.h"
#include "player_command.h"

void exec_player_command(struct client_entry *client,
    struct server *server, char *line)
{
    char **command = str_to_array(line, " ");

    if (command == NULL)
        return;
    for (int i = 0; i < MAX_COMMAND_PLAYER; i++) {
        if (command[0] != NULL &&
            !strcmp(player_command_list[i].command, command[0])) {
                (player_command_list[i].function) (command, client, server);
                free_array(command);
                return;
        }
    }
    if (command[0] != NULL)
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    free_array(command);
}
