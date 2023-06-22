/*
** EPITECH PROJECT, 2023
** utils_end_game.c
** File description:
** utils_end_game
*/

#include "macro.h"
#include "gui/events.h"

bool end_game(struct server *server)
{
    int count = 0;
    struct client_entry *player = NULL;
    char *name_team = NULL;

    for (int i = 0; i < server->nb_teams; i++) {
        count = 0;
        SLIST_FOREACH(player, &server->teams[i].players, next) {
            name_team = player->player_info->team->name;
            count += (player->player_info->level == MAX_LEVEL) ? 1 : 0;
        }
        if (count >= NB_PLAYER_LEVEL_MAX) {
            broadcast_to_guis(server, &notify_end_of_game, name_team);
            return true;
        }
    }
    return false;
}
