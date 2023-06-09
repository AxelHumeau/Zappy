/*
** EPITECH PROJECT, 2023
** incantation.c
** File description:
** incantation
*/

#include <string.h>
#include "macro.h"

void incantation(char **cmd, struct client_entry *client, struct server *)
{
    if (cmd[1] == NULL) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        write_buffer(&client->buf_to_send, client->fd);
    } else {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        write_buffer(&client->buf_to_send, client->fd);
    }
}
