/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setup_server
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timerfd.h>
#include "params.h"
#include "macro.h"

static void set_teams(struct server *server, char **teams)
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

static int get_port_and_team_name(char **params, int nb_params,
    struct server *server, int *index)
{
    if (*index >= nb_params)
        return 0;
    if (strcmp(params[*index], "-p") == 0) {
        server->port = get_port(params, index, nb_params);
        return get_port_and_team_name(params, nb_params, server, index);
    }
    if (strcmp(params[*index], "-n") == 0) {
        set_teams(server, get_team_names(params, index, nb_params));
        return get_port_and_team_name(params, nb_params, server, index);
    }
    return get_dimensions_freq_nb_client(params, nb_params, server, index);
}

int get_dimensions_freq_nb_client(char **params, int nb_params,
    struct server *server, int *index)
{
    if (strcmp(params[*index], "-x") == 0) {
        server->width = get_pos_int(params, index, nb_params);
        return get_port_and_team_name(params, nb_params, server, index);
    }
    if (strcmp(params[*index], "-y") == 0) {
        server->height = get_pos_int(params, index, nb_params);
        return get_port_and_team_name(params, nb_params, server, index);
    }
    if (strcmp(params[*index], "-f") == 0) {
        server->freq = get_pos_int(params, index, nb_params);
        return get_port_and_team_name(params, nb_params, server, index);
    }
    if (strcmp(params[*index], "-c") == 0) {
        server->max_players_per_team = get_pos_int(params, index, nb_params);
        return get_port_and_team_name(params, nb_params, server, index);
    }
    dprintf(2, "%s: Unknown option.\n", params[*index]);
    return EXIT_FAIL;
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
    timerfd_settime(server->timerfd, 0, &spec, NULL);
}

int get_server_params(char **params, int nb_params, struct server *server)
{
    int i = 1;

    server->height = -1;
    server->width = -1;
    server->teams = NULL;
    server->nb_teams = -1;
    server->max_players_per_team = -1;
    server->freq = -1;
    server->timestamp = 0;
    server->resources_time = 0;
    if (get_port_and_team_name(params, nb_params, server, &i) != EXIT_SUCCESS)
        return EXIT_FAIL;
    if (server->height == -1 || server->width == -1 ||
        server->teams == NULL || server->nb_teams <= 0 ||
        server->max_players_per_team == -1 || server->freq == -1)
        return EXIT_FAIL;
    for (size_t i = 0; i < server->nb_teams; i++)
        server->teams[i].nb_slots_left = server->max_players_per_team;
    init_timer(server);
    return EXIT_SUCCESS;
}
