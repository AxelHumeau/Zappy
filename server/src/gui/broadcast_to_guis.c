/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** broadcast_to_guis
*/

#include "gui/events.h"

int broadcast_to_guis(struct server *server, event_func_t *function, ...)
{
    va_list ap;
    struct client_entry *client;

    va_start(ap, function);
    SLIST_FOREACH(client, &server->clients, next) {
        if (client->is_gui && function(client, &ap)) {
            va_end(ap);
            return EXIT_FAILURE;
        }
    }
    va_end(ap);
    return EXIT_SUCCESS;
}
