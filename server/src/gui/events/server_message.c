/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** egg
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "gui/events.h"

int notify_server_message(struct client_entry *client, va_list *args)
{
    char *message = va_arg(*args, char *);
    char *result = NULL;

    asprintf(&result, "smg %s\n", message);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_end_of_game(struct client_entry *client, va_list *args)
{
    char *team_name = va_arg(*args, char *);
    char *result = NULL;

    asprintf(&result, "seg %s\n", team_name);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
