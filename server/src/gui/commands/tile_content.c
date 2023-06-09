/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_size
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int send_tile_content(char **args, struct server *server,
    struct client_entry *client)
{
    int x = 0;
    int y = 0;
    char *result = NULL;

    if (args[1] == NULL || args[2] == NULL)
        return EXIT_FAILURE;
    x = atoi(args[1]);
    y = atoi(args[2]);
    if (x < 0 || y < 0 || x >= server->width || y >= server->height)
        return EXIT_FAILURE;
    asprintf(&result, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n", x, y,
        server->maps[y][x].resources[FOOD],
        server->maps[y][x].resources[LINEMATE],
        server->maps[y][x].resources[DERAUMERE],
        server->maps[y][x].resources[SIBUR],
        server->maps[y][x].resources[MENDIANE],
        server->maps[y][x].resources[PHIRAS],
        server->maps[y][x].resources[THYSMANE]);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    return EXIT_SUCCESS;
}
