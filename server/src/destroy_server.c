/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** destroy_server
*/

#include <unistd.h>
#include "server.h"
#include "gui/events.h"

static void destroy_game(struct server *server)
{
    for (int y = 0; y < server->height; y++)
        free(server->maps[y]);
    free(server->maps);
}

static void destroy_eggs(struct server *server)
{
    struct egg *tmp = NULL;

    for (struct egg *egg = server->list_eggs.lh_first; egg;) {
        tmp = egg->next.le_next;
        free(egg);
        egg = tmp;
    }
}

static struct client_entry *get_player(struct team *team, int id,
    int nb_teams)
{
    struct client_entry *entry;

    if (id < 0 || nb_teams <= 0)
        return NULL;
    SLIST_FOREACH(entry, &team->players, next) {
        if (entry->id == id)
            return entry;
    }
    return get_player(team + 1, id, nb_teams - 1);
}

void destroy_player(struct client_entry *client, struct server *server)
{
    struct client_entry *player =
        get_player(server->teams, client->id, server->nb_teams);

    if (player != NULL) {
        SLIST_REMOVE(&client->player_info->team->players,
            player, client_entry, next);
        free(player);
    }
    if (client->is_role_defined && !client->is_gui)
        broadcast_to_guis(server, &notify_death, client->id);
}

void destroy_server(struct server *server)
{
    struct client_entry *tmp = NULL;

    destroy_clients(server);
    destroy_eggs(server);
    for (int i = 0; i < server->nb_teams; i++)
        for (struct client_entry *client = server->teams[i].players.slh_first;
            client; client = tmp) {
            tmp = client->next.sle_next;
            free(client);
        }
    free(server->teams);
    destroy_game(server);
    close(server->listening_fd);
    close(server->sig_fd);
}
