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

static void get_players_ritual(struct client_entry *client,
struct server *server, elevation_t ritual, struct client_entry **list_players)
{
    int index = 1;
    int id_count = 1;
    struct client_entry *player = NULL;
    struct position player_pos = {0};
    struct position pos = {client->player_info.x, client->player_info.y};

    list_players[0] = client;
    list_players[ritual.nb_players] = NULL;
    while (index != ritual.nb_players) {
        SLIST_FOREACH(player, &server->clients, next) {
            player_pos.x = player->player_info.x;
            player_pos.y = player->player_info.y;
            if (is_player(player, client) && player_pos.x == pos.x &&
                player_pos.y == pos.y && id_count == player->id) {
                list_players[index] = player;
                index++;
            }
        }
        id_count++;
    }
}

static struct client_entry **ritual_player(struct client_entry *client,
    struct server *server, int count, elevation_t ritual)
{
    struct client_entry **list_players = NULL;
    int nb_players = ritual.nb_players;

    if (count < ritual.nb_players)
        return NULL;
    list_players = malloc(sizeof(struct client_entry *) * (nb_players + 1));
    if (list_players == NULL)
        return NULL;
    get_players_ritual(client, server, ritual, list_players);
    return list_players;
}

static struct client_entry **enough_player(struct client_entry *client,
    struct server *server, elevation_t ritual)
{
    struct client_entry *player = NULL;
    int x = 0;
    int y = 0;
    struct position pos = {client->player_info.x, client->player_info.y};
    int count = 1;

    SLIST_FOREACH(player, &server->clients, next) {
        y = player->player_info.y;
        x = player->player_info.x;
        if (is_player(player, client) && y == pos.y && x == pos.x)
            count++;
    }
    return ritual_player(client, server, count, ritual);
}

void send_ritual_message(struct server *server, struct client_entry **list,
    bool is_elevate)
{
    for (int i = 0; list[i] != NULL; i++) {
        if (is_elevate)
            add_to_buffer(&list[i]->buf_to_send, ELEVATION, strlen(ELEVATION));
        else
            add_to_buffer(&list[i]->buf_to_send, KO, strlen(KO));
    }
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
    for (int i = 1; i < NB_RESOURCES; i++) {
        if (ritual.resource[i] != 0 && map_resources[i] < ritual.resource[i])
            can_ritual = false;
    }
    list_players = enough_player(client, server, ritual);
    if (can_ritual && list_players != NULL)
        return list_players;
    return NULL;
}
