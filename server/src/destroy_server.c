/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** destroy_server
*/

#include "server.h"
#include <unistd.h>

void destroy_game(struct server *server)
{
    for (int y = 0; y < server->height; y++)
        free(server->maps[y]);
    free(server->maps);
}

void destroy_server(struct server *server)
{
    struct client_entry *tmp = NULL;

    for (size_t i = 0; i < server->nb_teams; i++)
        for (struct client_entry *client = server->teams[i].players.slh_first;
            client; client = tmp) {
            tmp = client->next.sle_next;
            free(client);
        }
    destroy_clients(server);
    free(server->teams);
    destroy_game(server);
    close(server->listening_fd);
    close(server->sig_fd);
}
