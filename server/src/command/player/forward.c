/*
** EPITECH PROJECT, 2023
** forward.c
** File description:
** forward
*/

#include <string.h>
#include "macro.h"

static void replace_player(struct client_entry *client, struct server *server)
{
    if (client->player_info.x < 0)
        client->player_info.x = server->width - 1;
    if (client->player_info.x == server->width)
        client->player_info.x = 0;
    if (client->player_info.y < 0)
        client->player_info.y = server->height - 1;
    if (client->player_info.y == server->height)
        client->player_info.y = 0;
}

void forward(char *cmd, struct client_entry *client, struct server *server)
{
    enum direction direction_player = client->player_info.direction;

    if (cmd[0] == '\0') {
        client->player_info.x += DIRECTION[direction_player][0];
        client->player_info.y += DIRECTION[direction_player][1];
        replace_player(client, server);
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
