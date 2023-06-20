/*
** EPITECH PROJECT, 2023
** utils_incatation.c
** File description:
** utils_incantation
*/

#include <string.h>
#include <stdio.h>
#include "elevation_level.h"
#include "macro.h"

static void put_player_ritual(struct client_entry **list_players,
    struct client_entry *player, bool put_player, int *index)
{
    if (put_player) {
        list_players[(*index)] = player;
        (*index)++;
    }
}

static void get_players_ritual(struct client_entry *client,
struct server *server, elevation_t ritual, struct client_entry **list_players)
{
    int index = 1;
    int id = 1;
    struct client_entry *player = NULL;
    player_t entry;
    bool put_player = true;

    printf("ENTER RITUAL\n");
    while (index != ritual.nb_players) {
        SLIST_FOREACH(player, &server->clients, next) {
            entry = player->player_info;
            put_player = is_player(player, client) && same_pos(player, client)
                && id == player->id && entry.level == ritual.level;
            put_player_ritual(list_players, player, put_player, &index);
        }
        id++;
    }
    printf("EXIT RITUAL\n");
}

static struct client_entry **ritual_player(struct client_entry *client,
    struct server *server, int count, elevation_t ritual)
{
    struct client_entry **list_players = NULL;
    int nb_players = ritual.nb_players;

    if (count < ritual.nb_players) {
        printf("NOT ENOUGH PLAYER SAME LEVEL\n");
        return NULL;
    }
    list_players = malloc(sizeof(struct client_entry *) * (nb_players + 1));
    if (list_players == NULL)
        return NULL;
    list_players[0] = client;
    list_players[ritual.nb_players] = NULL;
    get_players_ritual(client, server, ritual, list_players);
    return list_players;
}

static struct client_entry **enough_player(struct client_entry *client,
    struct server *server, elevation_t ritual)
{
    struct client_entry *player = NULL;
    int count = 1;

    SLIST_FOREACH(player, &server->clients, next) {
        if (is_player(player, client) && same_pos(player, client) &&
            player->player_info.level == ritual.level)
            count++;
    }
    return ritual_player(client, server, count, ritual);
}

struct client_entry **condition_ritual(struct client_entry *client,
    struct server *server)
{
    struct position pos = {client->player_info.x, client->player_info.y};
    elevation_t ritual;
    size_t map_resources[NB_RESOURCES];
    bool can_ritual = true;
    size_t size = sizeof(size_t[NB_RESOURCES]);
    struct client_entry **list_players = NULL;

    memcpy(&map_resources, server->maps[pos.y][pos.x].resources, size);
    for (int i = 0; i < NB_LEVEL; i++) {
        if (client->player_info.level == elevation_ritual[i].level)
            ritual = elevation_ritual[i];
    }
    for (int i = 1; i < NB_RESOURCES; i++)
        can_ritual = (ritual.resource[i] != 0 &&
            map_resources[i] < ritual.resource[i]) ? false : can_ritual;
    list_players = enough_player(client, server, ritual);
    if (can_ritual && list_players != NULL)
        return list_players;
    free(list_players);
    return NULL;
}
