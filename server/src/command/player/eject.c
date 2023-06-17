/*
** EPITECH PROJECT, 2023
** eject.c
** File description:
** eject
*/

#include <string.h>
#include "macro.h"

void eject(char *cmd, struct client_entry *client, struct server *)
{
    if (cmd[0] == '\0')
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
    else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
