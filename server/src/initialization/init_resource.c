/*
** EPITECH PROJECT, 2023
** init_resources.c
** File description:
** init_resource
*/

#include <stdio.h>
#include "server.h"
#include "macro.h"

static int resources_left(size_t resource[])
{
    bool empty = true;
    int select_resource = rand() % NB_RESOURCES;

    for (int i = 0; i < NB_RESOURCES; i++) {
        if (resource[i] != 0) {
            empty = false;
            break;
        }
    }
    if (empty)
        return -1;
    while (resource[select_resource] <= 0)
        select_resource = rand() % NB_RESOURCES;
    return select_resource;
}

static void place_resource(struct server *server, size_t *resource, int index)
{
    int pos_y = rand() % server->height;
    int pos_x = rand() % server->width;

    server->maps[pos_y][pos_x].resources[index]++;
    resource[index]--;
}

void set_resource_map(struct server *server)
{
    size_t resource[NB_RESOURCES] = {
        DENSITY[FOOD] * server->width * server->height,
        DENSITY[LINEMATE] * server->width * server->height,
        DENSITY[DERAUMERE] * server->width * server->height,
        DENSITY[SIBUR] * server->width * server->height,
        DENSITY[MENDIANE] * server->width * server->height,
        DENSITY[PHIRAS] * server->width * server->height,
        DENSITY[THYSMANE] * server->width * server->height,
    };
    int select_resource = resources_left(resource);

    while (select_resource != -1) {
        place_resource(server, resource, select_resource);
        select_resource = resources_left(resource);
    }
}
