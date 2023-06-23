/*
** EPITECH PROJECT, 2023
** utils_player.c
** File description:
** utils_player
*/

#include <stdio.h>
#include "macro.h"
#include "gui/events.h"

void init_entry(struct client_entry *entry)
{
    entry->is_gui = false;
    entry->is_role_defined = false;
    entry->timer = -1;
    entry->food_time = 0;
    entry->is_dead = false;
    entry->ritual = false;
    entry->laying_egg = false;
    entry->egg = NULL;
}

void set_position_player(struct server *server, player_t *info,
    struct team *team)
{
    struct egg *egg_entity = NULL;

    SLIST_FOREACH(egg_entity, &server->list_eggs, next) {
        if (egg_entity->team == team) {
            info->x = egg_entity->x;
            info->y = egg_entity->y;
            broadcast_to_guis(server, &notify_egg_connection, egg_entity->id);
            SLIST_REMOVE(&server->list_eggs, egg_entity, egg, next);
            free(egg_entity);
            return;
        }
    }
    info->x = rand() % server->width;
    info->y = rand() % server->height;
}

bool is_player(struct client_entry *player, struct client_entry *client)
{
    return player->is_role_defined && !player->is_gui && client != player;
}

bool same_pos(struct client_entry *entry, struct client_entry *client)
{
    struct position entry_pos = {entry->player_info->x, entry->player_info->y};
    struct position pos = {client->player_info->x, client->player_info->y};

    return entry_pos.x == pos.x && entry_pos.y == pos.y;
}

void display_player(struct server *server)
{
    struct client_entry *player = NULL;
    int list[10][10] = {{0}};

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            list[i][j] = -1;
    }
    SLIST_FOREACH(player, &server->clients, next) {
        if (player->is_role_defined && !player->is_gui)
            list[player->player_info->y][player->player_info->x] = player->id;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf((list[i][j] == -1) ? "[ ] " : "[%d] ", list[i][j]);
        printf("\n");
    }

}
