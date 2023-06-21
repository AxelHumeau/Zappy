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
    struct client_entry *client;

    va_start(ap, function);
    SLIST_FOREACH(client, &server->clients, next) {
        va_copy(copy, ap);
        if (client->is_role_defined && client->is_gui
            && function(client, &copy)) {
            va_end(ap);
            va_end(copy);
            return EXIT_FAILURE;
        }
        va_end(copy);
    }
    va_end(ap);
    return EXIT_SUCCESS;
}
