/*
** EPITECH PROJECT, 2023
** connect_nbr.c
** File description:
** connect_nbr
*/

#include <stdio.h>
#include <string.h>
#include "macro.h"

void connect_nbr(char **cmd, struct client_entry *client,
    struct server *)
{
    char *slots_left = NULL;

    if (cmd[1] == NULL) {
        asprintf(&slots_left, "%d\n",
            client->player_info.team->nb_slots_left);
        add_to_buffer(&client->buf_to_send, slots_left, strlen(slots_left));
        write_buffer(&client->buf_to_send, client->fd);
        free(slots_left);
    } else {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        write_buffer(&client->buf_to_send, client->fd);
    }
}
