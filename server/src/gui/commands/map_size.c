/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_size
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int send_map_size(char **, struct server *server, struct client_entry *client)
{
    char *x;
    char *y;

    add_to_buffer(&client->buf_to_send, "msz ", 4);
    asprintf(&x, "%d", server->width);
    asprintf(&y, "%d", server->height);
    add_to_buffer(&client->buf_to_send, x, strlen(x));
    add_to_buffer(&client->buf_to_send, " ", 1);
    add_to_buffer(&client->buf_to_send, y, strlen(y));
    add_to_buffer(&client->buf_to_send, "\n", 1);
    free(x);
    free(y);
    return EXIT_SUCCESS;
}
