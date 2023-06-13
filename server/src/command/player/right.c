/*
** EPITECH PROJECT, 2023
** right.c
** File description:
** right
*/

#include <string.h>
#include "macro.h"

void right(char **cmd, struct client_entry *client, struct server *)
{
    if (cmd[1] == NULL) {
        client->player_info.direction =
        (enum direction) ((client->player_info.direction + 1) % NB_DIRECTIONS);
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
