/*
** EPITECH PROJECT, 2023
** incantation.c
** File description:
** incantation
*/

#include <string.h>
#include "macro.h"
#include "gui/events.h"

void incantation(char *cmd, struct client_entry *client,
    struct server *server)
{
    if (cmd[0] == '\0') {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        broadcast_to_guis(server, &notify_start_of_incantation,
            client->id, &client->player_info, 0);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
