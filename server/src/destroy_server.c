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
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++)
            free(server->maps[y][x].resources);
        free(server->maps[y]);
    }
    free(server->maps);
}

void destroy_server(struct server *server)
{
    free(server->teams);
    destroy_clients(server);
    destroy_game(server);
    close(server->listening_fd);
    close(server->sig_fd);
}
