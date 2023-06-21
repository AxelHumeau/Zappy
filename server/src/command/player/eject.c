/*
** EPITECH PROJECT, 2023
** eject.c
** File description:
** eject
*/

#include <string.h>
#include <stdio.h>
#include "macro.h"
#include "gui/events.h"

static void send_eject_message(struct client_entry *player, int i)
{
    char *message = NULL;
    enum direction dir = player->player_info->direction;
    int index = (DIRECTION_ZONE[dir] + (ZONE_SIZE - 2 * i)) % ZONE_SIZE;

    asprintf(&message, "eject: %d\n", index);
    add_to_buffer(&player->buf_to_send, message, strlen(message));
    free(message);
}

static void move_player(struct client_entry *client,
    struct client_entry *player, struct server *server)
{
    struct position save_pos = {player->player_info->x, player->player_info->y};
    struct position move = {0};

    player->player_info->x += DIRECTION[client->player_info->direction][0];
    player->player_info->y += DIRECTION[client->player_info->direction][1];
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        move.x = save_pos.x - player->player_info->x;
        move.y = save_pos.y - player->player_info->y;
        if (move.x == DIRECTION[i][0] && move.y == DIRECTION[i][1])
            send_eject_message(player, i);
    }
    player->player_info->x += (player->player_info->x < 0) ? server->width : 0;
    player->player_info->y += (player->player_info->y < 0) ? server->height : 0;
}

static bool eject_player(struct client_entry *client, struct server *server)
{
    bool eject = false;
    struct client_entry *player = NULL;
    int x = 0;
    int y = 0;

    SLIST_FOREACH(player, &server->clients, next) {
        x = player->player_info->x;
        y = player->player_info->y;
        if (is_player(player, client) &&
            x == client->player_info->x && y == client->player_info->y) {
            move_player(client, player, server);
            eject = true;
        }
    }
    return eject;
}

void eject(char *cmd, struct client_entry *client, struct server *server)
{
    if (cmd[0] == '\0' && eject_player(client, server)) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        broadcast_to_guis(server, &notify_expulsion, client->id);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
