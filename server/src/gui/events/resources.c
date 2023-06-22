/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** resources
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "gui/events.h"

int notify_resource_dropping(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    int resource_nb = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "pdr %d %d\n", player_id, resource_nb);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_resource_collecting(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    int resource_nb = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "pgt %d %d\n", player_id, resource_nb);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
