/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** player_infos
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static player_t *get_player(struct team *team, int id, int nb_teams)
{
    struct client_entry *entry;

    if (id < 0 || nb_teams <= 0)
        return NULL;
    SLIST_FOREACH(entry, &team->players, next) {
        if (entry->id == id)
            return &entry->player_info;
    }
    return get_player(team + 1, id, nb_teams - 1);
}

static int get_id_from_args(char **args)
{
    int id = 0;

    if (args[1] == NULL)
        return -1;
    id = atoi(args[1]);
    if (id < 0)
        return -1;
    return id;
}

int send_player_pos(char **args, struct server *server,
    struct client_entry *client)
{
    int id = get_id_from_args(args);
    player_t *player = NULL;
    char *result = NULL;

    if (id == -1)
        return EXIT_FAILURE;
    player = get_player(server->teams, id, server->nb_teams);
    if (player == NULL)
        return EXIT_FAILURE;
    asprintf(&result, "ppo %d %d %d %d\n", id, player->x, player->y,
        player->direction + 1);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int send_player_level(char **args, struct server *server,
    struct client_entry *client)
{
    int id = get_id_from_args(args);
    player_t *player = NULL;
    char *result = NULL;

    if (id == -1)
        return EXIT_FAILURE;
    player = get_player(server->teams, id, server->nb_teams);
    if (player == NULL)
        return EXIT_FAILURE;
    asprintf(&result, "plv %d %d\n", id, player->level);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}

int send_player_inventory(char **args, struct server *server,
    struct client_entry *client)
{
    int id = get_id_from_args(args);
    player_t *player = NULL;
    char *result = NULL;

    if (id == -1)
        return EXIT_FAILURE;
    player = get_player(server->teams, id, server->nb_teams);
    if (player == NULL)
        return EXIT_FAILURE;
    asprintf(&result, "pin %d %d %d %ld %ld %ld %ld %ld %ld %ld\n",
        id, player->x, player->y,
        player->inventory[FOOD], player->inventory[LINEMATE],
        player->inventory[DERAUMERE], player->inventory[SIBUR],
        player->inventory[MENDIANE], player->inventory[PHIRAS],
        player->inventory[THYSMANE]);
    add_to_buffer(&client->buf_to_send, result, strlen(result));
    free(result);
    return EXIT_SUCCESS;
}
