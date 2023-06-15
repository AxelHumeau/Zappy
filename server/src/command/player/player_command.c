/*
** EPITECH PROJECT, 2023
** player_command.c
** File description:
** player_command
*/

#include <string.h>
#include "macro.h"
#include "player_command.h"

void handle_player_command(struct client_entry *client, char *line)
{
    if (!strcmp(line, "\0"))
        return;
    if (client->count_command != 10)
        client->command[client->count_command++] = strdup(line);
}

static void clean_player_command(struct client_entry *client)
{
    size_t size = 0;

    free(client->command[0]);
    client->count_command--;
    size = sizeof(char *) * client->count_command;
    memmove(&client->command[0], &client->command[1], size);
}

static void time_command(struct client_entry *client,
    struct server *server, char **command_line, command_t command)
{
    if (client->timer == -1)
        client->timer = server->timestamp;
    else if (server->timestamp - client->timer >= command.cooldown) {
        (command.function) (command_line, client, server);
        clean_player_command(client);
        client->timer = -1;
    }
}

void exec_player_command(struct client_entry *client,
    struct server *server, char *line)
{
    char **command = str_to_array(line, " ");

    if (command == NULL)
        return;
    for (int i = 0; i < NB_COMMAND_PLAYER; i++) {
        if (command[0] != NULL &&
            !strcmp(player_command_list[i].command, command[0])) {
                time_command(client, server, command, player_command_list[i]);
                free_array(command);
                return;
        }
    }
    add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    clean_player_command(client);
    free_array(command);
}
