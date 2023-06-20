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

void send_ritual_message(struct client_entry *client, struct server *server,
    struct client_entry **list, bool is_elevate)
{
    int timer = 0;

    if (list == NULL) {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        return;
    }
    for (int i = 0; list[i] != NULL; i++) {
        if (is_elevate) {
            timer = list[i]->timer;
            list[i]->timer = (list[i] != client) ? TIMER_INCANTATION : timer;
            add_to_buffer(&list[i]->buf_to_send, ELEVATION, strlen(ELEVATION));
        } else
            add_to_buffer(&list[i]->buf_to_send, KO, strlen(KO));
    }
}

static void remove_resources_map(struct client_entry *client,
    struct server *server)
{
    struct position pos = {client->player_info.x, client->player_info.y};
    elevation_t ritual;

    for (int i = 0; i < NB_LEVEL; i++) {
        if (client->player_info.level == elevation_ritual[i].level)
            ritual = elevation_ritual[i];
    }
    for (int i = 0; i < NB_RESOURCES; i++)
        server->maps[pos.y][pos.x].resources[i] -= ritual.resource[i];
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
        send_ritual_message(client, server, list_players, false);
    client->ritual = false;
    free(list_players);
}
