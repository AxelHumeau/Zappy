/*
** EPITECH PROJECT, 2023
** left.c
** File description:
** left
*/

#include <string.h>
#include "macro.h"

void left(char *cmd, struct client_entry *client, struct server *)
{
    if (cmd[0] == '\0') {
        client->player_info.direction = (client->player_info.direction == UP) ?
            (NB_DIRECTIONS - 1) : client->player_info.direction - 1;
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
