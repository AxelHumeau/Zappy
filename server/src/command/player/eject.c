/*
** EPITECH PROJECT, 2023
** eject.c
** File description:
** eject
*/

#include <string.h>
#include "macro.h"
#include "gui/events.h"

void eject(char **cmd, struct client_entry *client,
    struct server *server)
{
    if (cmd[1] == NULL) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        broadcast_to_guis(server, &notify_expulsion, client->id);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
