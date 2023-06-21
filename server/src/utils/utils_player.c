/*
** EPITECH PROJECT, 2023
** utils_player.c
** File description:
** utils_player
*/

#include <stdio.h>
#include "macro.h"

int *get_list_ids(struct client_entry **list_players, int size)
{
    int *list_ids = NULL;
    int index = 0;

    if (size == 0)
        return NULL;
    list_ids = malloc(sizeof(int) * size);
    for (int i = 1; list_players[i] != NULL; i++) {
        list_ids[index] = list_players[i]->id;
        index++;
    }
    return list_ids;
}

int list_ids_size(struct client_entry **list_players)
{
    int size = 0;

    for (int i = 1; list_players[i] != NULL; i++)
        size++;
    return size;
}

bool is_player(struct client_entry *player, struct client_entry *client)
{
    return player->is_role_defined && !player->is_gui && client != player;
}

bool same_pos(struct client_entry *entry, struct client_entry *client)
{
    struct position entry_pos = {entry->player_info.x, entry->player_info.y};
    struct position pos = {client->player_info.x, client->player_info.y};

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
            list[player->player_info.y][player->player_info.x] = player->id;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf((list[i][j] == -1) ? "[ ] " : "[%d] ", list[i][j]);
        printf("\n");
    }

}
