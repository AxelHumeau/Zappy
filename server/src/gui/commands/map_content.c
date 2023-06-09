/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>
#include "gui/commands.h"

int map_content(char **, struct server *server, struct client_entry *client)
{
    char *x;
    char *y;

    for (int i = 0; i < server->height; i++)
        for (int j = 0; j < server->width; j++) {
            asprintf(&x, "%d", j);
            asprintf(&y, "%d", i);
            tile_content((char *[]) {"bct", x, y}, server, client);
            free(x);
            free(y);
        }
    return EXIT_SUCCESS;
}
