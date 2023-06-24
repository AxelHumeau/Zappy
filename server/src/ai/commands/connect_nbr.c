/*
** EPITECH PROJECT, 2023
** connect_nbr.c
** File description:
** connect_nbr
*/

#include <stdio.h>
#include <string.h>
#include "macro.h"

void connect_nbr(char *cmd, struct client_entry *client,
    struct server *)
{
    char *slots_left = NULL;

    if (cmd[0] == '\0') {
        asprintf(&slots_left, "%d\n",
            client->player_info->team->nb_slots_left);
        printf("slot left : %s", slots_left);
        add_to_buffer(&client->buf_to_send, slots_left, strlen(slots_left));
        free(slots_left);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
