/*
** EPITECH PROJECT, 2023
** utils_broadcast.c
** File description:
** utils_broadcast
*/

#include <stdio.h>
#include "macro.h"

void debug_map_broadcast(struct client_entry *client,
    struct client_entry *player, struct position zone[])
{
    struct position sender = {client->player_info.x, client->player_info.y};
    struct position target = {player->player_info.x, player->player_info.y};
    int list[10][10] = {{0}};
    int count = DIRECTION_ZONE[player->player_info.direction];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            list[i][j] = -1;
    }
    list[sender.y][sender.x] = 9;
    list[target.y][target.x] = 0;
    for (int i = 0; i < ZONE_SIZE; i++) {
        list[zone[i].y][zone[i].x] = (count % 8 == 0) ? 8 : count % 8;
        count++;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf((list[i][j] == -1) ? "[ ] " : "[%d] ", list[i][j]);
        printf("\n");
    }
}
