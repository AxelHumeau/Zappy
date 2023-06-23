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
    struct position pos = {player->player_info->x, player->player_info->y};
    struct position move = {0};
    int width = server->width;
    int height = server->height;

    player->player_info->x += DIRECTION[client->player_info->direction][0];
    player->player_info->y += DIRECTION[client->player_info->direction][1];
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        move.x = pos.x - player->player_info->x;
        move.y = pos.y - player->player_info->y;
        if (move.x == DIRECTION[i][0] && move.y == DIRECTION[i][1])
            send_eject_message(player, i);
    }
    player->player_info->x += (player->player_info->x < 0) ? width : 0;
    player->player_info->y += (player->player_info->y < 0) ? height : 0;
}

static void destroy_eggs(struct client_entry *client, struct server *server)
{
    struct position pos = {client->player_info->x, client->player_info->y};
    struct egg *tmp = NULL;

    for (struct egg *egg_entity = server->list_eggs.slh_first; egg_entity;) {
        tmp = egg_entity->next.sle_next;
        if (egg_entity->x == pos.x && egg_entity->y == pos.y) {
            SLIST_REMOVE(&server->list_eggs, egg_entity, egg, next);
            broadcast_to_guis(server, &notify_egg_death, egg_entity->id);
            free(egg_entity);
        }
        egg_entity = tmp;
    }
}

static bool eject_player(struct client_entry *client, struct server *server)
{
    bool eject = false;
    struct client_entry *player = NULL;

    SLIST_FOREACH(player, &server->clients, next) {
        if (is_player(player, client) &&
                player->player_info->x == client->player_info->x &&
                player->player_info->y == client->player_info->y) {
            move_player(client, player, server);
            eject = true;
        }
    }
    destroy_eggs(client, server);
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
