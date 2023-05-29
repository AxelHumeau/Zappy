/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** get_params
*/

#include <stdlib.h>
#include <string.h>
#include "params.h"
#include "server.h"

int get_port(char **params, int *start, int nb_params)
{
    int port = 0;

    if (++(*start) >= nb_params)
        return -1;
    port  = atoi(params[*start]);
    (*start)++;
    if (port <= 0 || port >= MAX_PORT_NUMBER)
        return -1;
    return port;
}

int get_pos_int(char **params, int *start, int nb_params)
{
    int dimension = 0;

    if (++(*start) >= nb_params)
        return -1;
    dimension  = atoi(params[*start]);
    (*start)++;
    if (dimension <= 0)
        return -1;
    return dimension;
}

char **get_team_names(char **params, int *start, int nb_params)
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
