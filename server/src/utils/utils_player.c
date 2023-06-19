/*
** EPITECH PROJECT, 2023
** utils_player.c
** File description:
** utils_player
*/

#include <stdio.h>
#include "macro.h"

bool is_player(struct client_entry *player, struct client_entry *client)
{
    return player->is_role_defined && !player->is_gui && client != player;
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
