/*
** EPITECH PROJECT, 2023
** init_resources.c
** File description:
** init_resource
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "macro.h"

static int resources_left(int resource[])
{
    bool empty = true;
    int select_resource = rand() % NB_RESOURCES;

    for (int i = 0; i < NB_RESOURCES; i++) {
        if (resource[i] > 0) {
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

static void place_resource(struct server *server, int *resource, int index,
    bool increment)
{
    int pos_y = rand() % server->height;
    int pos_x = rand() % server->width;

    server->maps[pos_y][pos_x].resources[index]++;
    if (increment)
        server->map_resource[index]++;
    resource[index]--;
}

static void check_stock_resources(int *resource)
{
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (resource[i] == 0)
            resource[i]++;
    }
}

void refill_resources(struct server *server)
{
    size_t nb = server->multiplier_resource;
    int resource[NB_RESOURCES] = {
        nb * server->ref_resource[FOOD] - server->map_resource[FOOD],
        nb * server->ref_resource[LINEMATE] - server->map_resource[LINEMATE],
        nb * server->ref_resource[DERAUMERE] - server->map_resource[DERAUMERE],
        nb * server->ref_resource[SIBUR] - server->map_resource[SIBUR],
        nb * server->ref_resource[MENDIANE] - server->map_resource[MENDIANE],
        nb * server->ref_resource[PHIRAS] - server->map_resource[PHIRAS],
        nb * server->ref_resource[THYSMANE] - server->map_resource[THYSMANE],
    };
    int select_resource = 0;

    select_resource = resources_left(resource);
    while (select_resource != -1) {
        place_resource(server, resource, select_resource, true);
        select_resource = resources_left(resource);
    }
}

void set_resource_map(struct server *server)
{
    int resource[NB_RESOURCES] = {
        DENSITY[FOOD] * server->width * server->height,
        DENSITY[LINEMATE] * server->width * server->height,
        DENSITY[DERAUMERE] * server->width * server->height,
        DENSITY[SIBUR] * server->width * server->height,
        DENSITY[MENDIANE] * server->width * server->height,
        DENSITY[PHIRAS] * server->width * server->height,
        DENSITY[THYSMANE] * server->width * server->height,
    };
    int select_resource = 0;

    check_stock_resources(resource);
    memcpy(&server->ref_resource, resource, sizeof(int[NB_RESOURCES]));
    memcpy(&server->map_resource, resource, sizeof(int[NB_RESOURCES]));
    select_resource = resources_left(resource);
    while (select_resource != -1) {
        place_resource(server, resource, select_resource, false);
        select_resource = resources_left(resource);
    }
}
