/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** death
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "gui/events.h"

int notify_death(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "pdi %d\n", player_id);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
