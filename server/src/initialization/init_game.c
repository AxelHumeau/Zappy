/*
** EPITECH PROJECT, 2023
** init_game.c
** File description:
** init_game
*/

#include <stdio.h>
#include "server.h"
#include "macro.h"

static int init_map(struct server *server)
{
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++) {
            server->maps[y][x].resources = NULL;
            server->maps[y][x].nb_ressources = 0;
            server->maps[y][x].y = y;
            server->maps[y][x].x = x;
        }
    }
    set_resource_map(server);
    return EXIT_SUCCESS;
}

int init_game(struct server *server)
{
    server->maps = malloc(sizeof(struct tile *) * server->height);
    if (server->maps == NULL)
        return EXIT_FAIL;
    for (int y = 0; y < server->height; y++) {
        server->maps[y] = malloc(sizeof(struct tile) * server->width);
        if (server->maps[y] == NULL)
            return EXIT_FAIL;
    }
    if (init_map(server) != EXIT_SUCCESS)
        return EXIT_FAIL;
    return EXIT_SUCCESS;
}
