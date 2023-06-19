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

int notify_egg_laying(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "pfk %d\n", player_id);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_egg_layed(struct client_entry *client, va_list *args)
{
    egg_t *egg = va_arg(*args, egg_t *);
    int player_id = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "enw %d %d %d %d\n", egg->id, player_id, egg->x, egg->y);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_egg_connection(struct client_entry *client, va_list *args)
{
    int egg_id = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "ebo %d\n", egg_id);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_egg_death(struct client_entry *client, va_list *args)
{
    int egg_id = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "edi %d\n", egg_id);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
