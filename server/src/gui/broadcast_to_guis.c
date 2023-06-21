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
    va_list copy;
    int result = 0;
    struct client_entry *client;

    va_start(ap, function);
    SLIST_FOREACH(client, &server->clients, next) {
        va_copy(copy, ap);
        result = function(client, &copy);
        if (client->is_gui && result) {
            va_end(ap);
            va_end(copy);
            return EXIT_FAILURE;
        }
        va_end(copy);
    }
    va_end(ap);
    return EXIT_SUCCESS;
}
