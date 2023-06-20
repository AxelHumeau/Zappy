/*
** EPITECH PROJECT, 2023
** incantation.c
** File description:
** incantation
*/

#include <string.h>
#include <stdio.h>
#include "macro.h"
#include "elevation_level.h"
#include "gui/events.h"

static void remove_resources_map(struct client_entry *client,
    struct server *server)
{
    struct position pos = {client->player_info.x, client->player_info.y};
    size_t map_resources[NB_RESOURCES];
    bool can_ritual = true;
    size_t size = sizeof(size_t[NB_RESOURCES]);
    elevation_t ritual;

    memcpy(&map_resources, server->maps[pos.y][pos.x].resources, size);
    for (int i = 0; i < NB_LEVEL; i++) {
        if (client->player_info.level == elevation_ritual[i].level)
            ritual = elevation_ritual[i];
    }
}

static void do_elevation(struct client_entry *client, struct server *server,
    struct client_entry **list_players)
{
    char *message = NULL;

    remove_resources_map(client, server);
    for (int i = 0; list_players[i] != NULL; i++) {
        list_players[i]->player_info.level++;
        asprintf(&message, "Current level : %d\n", client->player_info.level);
        add_to_buffer(&list_players[i]->buf_to_send, message, strlen(message));
        free(message);
    }
    client->ritual = false;
}

void incantation(char *cmd, struct client_entry *client,
    struct server *server)
{
    struct client_entry **list_players = NULL;

    list_players = condition_ritual(client, server);
    if (cmd[0] == '\0' && list_players != NULL) {
        do_elevation(client, server, list_players);
        broadcast_to_guis(server, &notify_start_of_incantation,
            client->id, &client->player_info, 0);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    free(list_players);
}
