/*
** EPITECH PROJECT, 2023
** broadcast.c
** File description:
** broadcast
*/

#include <string.h>
#include "macro.h"
#include "gui/events.h"

void broadcast(char **cmd, struct client_entry *client,
    struct server *server)
{
    if (cmd[2] == NULL) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        broadcast_to_guis(server, &notify_broadcast,
            client->id, "Je suis un message");
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
