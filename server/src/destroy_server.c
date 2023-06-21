/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** destroy_server
*/

#include <unistd.h>
#include "server.h"

static void destroy_game(struct server *server)
{
    for (int y = 0; y < server->height; y++)
        free(server->maps[y]);
    free(server->maps);
}

static void destroy_eggs(struct server *server)
{
    struct egg *tmp = NULL;

    for (struct egg *egg = server->list_eggs.lh_first; egg;) {
        tmp = egg->next.le_next;
        free(egg);
        egg = tmp;
    }
}

void destroy_server(struct server *server)
{
    struct client_entry *tmp = NULL;

    for (int i = 0; i < server->nb_teams; i++)
        for (struct client_entry *client = server->teams[i].players.slh_first;
            client; client = tmp) {
            tmp = client->next.sle_next;
            free(client);
        }
    destroy_eggs(server);
    destroy_clients(server);
    free(server->teams);
    destroy_game(server);
    close(server->listening_fd);
    close(server->sig_fd);
}
