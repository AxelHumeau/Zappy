/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** get_params
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "params.h"
#include "server.h"
#include "macro.h"

static int get_port(char **params, int *start, int nb_params)
{
    int port = 0;

    if (++(*start) >= nb_params)
        return EXIT_FAIL;
    port = atoi(params[*start]);
    (*start)++;
    if (port <= 0 || port >= MAX_PORT_NUMBER)
        return EXIT_FAIL;
    return port;
}

static int get_pos_int(char **params, int *start, int nb_params)
{
    int dimension = 0;

    if (++(*start) >= nb_params)
        return EXIT_FAIL;
    dimension = atoi(params[*start]);
    (*start)++;
    if (dimension <= 0)
        return EXIT_FAIL;
    return dimension;
}

static char **get_team_names(char **params, int *start, int nb_params)
{
    char **names = malloc(sizeof(char *[1]));
    size_t count = 1;

    names[0] = NULL;
    if (++(*start) >= nb_params) {
        free(names);
        return NULL;
    }
    for (; *start < nb_params && params[*start][0] != '-'; (*start)++) {
        names = realloc(names, sizeof(char *[count + 1]));
        names[count - 1] = params[*start];
        names[count++] = NULL;
    }
    return names;
}

int get_port_and_team_name(char **params, int nb_params,
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
