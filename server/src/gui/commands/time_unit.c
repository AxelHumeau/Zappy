/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>
#include "gui/commands.h"

int send_time_request(char **, struct server *server,
    struct client_entry *client)
{
    char *response;

    asprintf(&response, "sgt %d\n", server->freq);
    add_to_buffer(&client->buf_to_send, response, strlen(response));
    free(response);
    return EXIT_SUCCESS;
}

int send_time_modification(char **args, struct server *server,
    struct client_entry *client)
{
    char *response;
    int new_frec = 0;

    if (args[1] == NULL)
        return EXIT_FAILURE;
    new_frec = atoi(args[1]);
    if (new_frec <= 0 )
        return EXIT_FAILURE;
    server->freq = new_frec;
    asprintf(&response, "sst %d\n", server->freq);
    add_to_buffer(&client->buf_to_send, response, strlen(response));
    free(response);
    return EXIT_SUCCESS;
}
