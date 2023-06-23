/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setup_server
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timerfd.h>
#include "params.h"
#include "macro.h"

void set_teams(struct server *server, char **teams)
{
    size_t len = 0;

    if (teams == NULL)
        return;
    for (; teams[len] != NULL; len++);
    server->teams = malloc(sizeof(struct team[len]));
    for (size_t i = 0; i < len; i++) {
        server->teams[i].name = teams[i];
        SLIST_INIT(&server->teams[i].players);
    }
    server->nb_teams = len;
    free(teams);
}

static void init_timer(struct server *server)
{
    time_t second = (server->freq == 1) ? 1 : 0;
    long nanosecond = (server->freq != 1) ? 1e9 / server->freq : 0;
    struct itimerspec spec = {
        {second, nanosecond},
        {second, nanosecond}
    };

    server->timerfd = timerfd_create(CLOCK_REALTIME, 0);
    server->resources_time = 0;
    server->multiplier_resource = 1;
    timerfd_settime(server->timerfd, 0, &spec, NULL);
}

static void set_server_default_values(struct server *server)
{
    server->height = -1;
    server->width = -1;
    server->teams = NULL;
    server->nb_teams = -1;
    server->max_players_per_team = -1;
    server->freq = 100;
    server->port = -1;
    server->timestamp = 0;
    server->nb_players = 0;
}

int get_server_params(char **params, int nb_params, struct server *server)
{
    int i = 1;

    set_server_default_values(server);
    if (get_port_and_team_name(params, nb_params, server, &i) != EXIT_SUCCESS)
        return EXIT_FAIL;
    if (server->height == -1 || server->width == -1 || server->port == -1 ||
        server->teams == NULL || server->nb_teams <= 0 ||
        server->max_players_per_team == -1 || server->freq == -1)
        return EXIT_FAIL;
    for (i = 0; i < server->nb_teams; i++)
        server->teams[i].nb_slots_left = server->max_players_per_team;
    init_timer(server);
    SLIST_INIT(&server->list_eggs);
    server->id_egg = 0;
    return EXIT_SUCCESS;
}
