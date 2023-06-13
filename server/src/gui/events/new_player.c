/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** new_player
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

int notify_new_player(struct server *, struct client_entry *client,
    player_t *player, int player_id)
{
    char *result = NULL;

    asprintf(&result, "pnw %d %d %d %d %d\n", player_id, player->x, player->y,
        player->orientation, player->level);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
