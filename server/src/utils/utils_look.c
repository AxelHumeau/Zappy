/*
** EPITECH PROJECT, 2023
** utils_look.c
** File description:
** utils_look
*/

#include "macro.h"

char *add_tiles_elem_string(struct server *server, struct client_entry *client,
    struct position pos, char *look_info)
{
    struct client_entry *player = NULL;

    SLIST_FOREACH(player, &server->clients, next) {
        if (is_player(player, client) &&
            player->player_info.y == pos.y && player->player_info.x == pos.x)
            look_info = concat_info_string(look_info, "player", true);
    }
    for (int i = 0; i < NB_RESOURCES; i++) {
        for (size_t nb = 0; nb < server->maps[pos.y][pos.x].resources[i]; nb++)
            look_info = concat_info_string(look_info, RESSOURCE_STR[i], true);
    }
    return look_info;
}
