/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** new_player
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "gui/events.h"

void send_new_player_str(struct client_entry *client, int player_id,
    player_t *player)
{
    char *result = NULL;

    asprintf(&result, "pnw %d %d %d %d %d\n", player_id, player->x, player->y,
        player->direction, player->level);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
}

int notify_new_player(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    player_t *player = va_arg(*args, player_t *);

    send_new_player_str(client, player_id, player);
    return EXIT_SUCCESS;
}
