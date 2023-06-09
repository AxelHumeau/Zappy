/*
** EPITECH PROJECT, 2023
** connect_nbr.c
** File description:
** connect_nbr
*/

#include <string.h>
#include "macro.h"

void connect_nbr(char **cmd, struct client_entry *client,
    struct server *server)
{
    if (cmd[1] == NULL) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        write_buffer(&client->buf_to_send, client->fd);
    } else {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        write_buffer(&client->buf_to_send, client->fd);
    }
}
