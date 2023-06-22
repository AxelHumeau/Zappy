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

static char *construct_start_incantation_str(player_t *player,
    int player_id, int *additional_player_ids, int nb_additional_players)
{
    char *result = NULL;
    char *tmp = NULL;
    int i = 0;

    asprintf(&result, "pic %d %d %d %d", player->x, player->y,
        player->level, player_id);
    for (; i < nb_additional_players; i++) {
        asprintf(&tmp, "%s %d", result, additional_player_ids[i]);
        free(result);
        result = tmp;
    }
    asprintf(&tmp, "%s\n", result);
    free(result);
    result = tmp;
    return result;
}

int notify_start_of_incantation(struct client_entry *client, va_list *args)
{
    int player_id = va_arg(*args, int);
    player_t *player = va_arg(*args, player_t *);
    int nb_additional_players = va_arg(*args, int);
    int *additional_player_ids = va_arg(*args, int *);
    char *result = NULL;

    result = construct_start_incantation_str(player, player_id,
        additional_player_ids, nb_additional_players);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int notify_end_of_incantation(struct client_entry *client, va_list *args)
{
    player_t *player = va_arg(*args, player_t *);
    int inc_result = va_arg(*args, int);
    char *result = NULL;

    asprintf(&result, "pie %d %d %d\n", player->x, player->y,
        inc_result);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
