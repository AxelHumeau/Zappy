/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_size
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int tile_content(char **args, struct server *server,
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
        server->maps[y][x].resources[0], server->maps[y][x].resources[1],
        server->maps[y][x].resources[2], server->maps[y][x].resources[3],
        server->maps[y][x].resources[4], server->maps[y][x].resources[5],
        server->maps[y][x].resources[6]);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    return EXIT_SUCCESS;
}
