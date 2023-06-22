/*
** EPITECH PROJECT, 2023
** fork.c
** File description:
** fork
*/

#include <string.h>
#include "macro.h"
#include "gui/events.h"

void fork_cmd(char *cmd, struct client_entry *client,
    struct server *server)
{
    if (cmd[0] == '\0') {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        broadcast_to_guis(server, &notify_egg_layed, client->egg, client->id);
        LIST_INSERT_HEAD(&server->list_eggs, client->egg, next);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    client->laying_egg = false;
}
