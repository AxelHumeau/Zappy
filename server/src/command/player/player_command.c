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
    struct server *server, char *line, command_t command)
{
    if (client->timer == -1)
        client->timer = server->timestamp;
    else if (server->timestamp - client->timer >= command.cooldown) {
        (command.function) (line + strlen(command.command), client, server);
        clean_player_command(client);
        client->timer = -1;
    }
}

void exec_player_command(struct client_entry *client,
    struct server *server, char *line)
{
    char *cmd = NULL;

    for (int i = 0; i < NB_COMMAND_PLAYER; i++) {
        cmd = player_command_list[i].command;
        if (!strncmp(cmd, line, strlen(cmd))) {
            time_command(client, server, line, player_command_list[i]);
            return;
        }
    }
    add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    clean_player_command(client);
}
