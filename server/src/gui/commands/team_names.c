/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** team_names
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int send_team_names(char **, struct server *server, struct client_entry *client)
{
    char *result = NULL;

    for (int i = 0; i < server->nb_teams; i++) {
        asprintf(&result, "tna %s\n", server->teams[i].name);
        add_to_buffer(&client->buf_to_send, result, strlen(result));
        free(result);
    }
    return EXIT_SUCCESS;
}
