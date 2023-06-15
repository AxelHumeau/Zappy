/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** new_player
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "gui/events.h"

int notify_broadcast(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    char *message = va_arg(*args, char *);
    char *result = NULL;

    asprintf(&result, "pbc %d %s\n", player_id, message);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
