/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** params
*/

#pragma once

#define MAX_PORT_NUMBER 65535
#include "server.h"

int get_port(char **params, int *start, int nb_params);
int get_pos_int(char **params, int *start, int nb_params);
char **get_team_names(char **params, int *start, int nb_params);
int get_server_params(char **params, int nb_params, struct server *server);
int get_dimensions_freq_nb_client(char **params, int nb_params,
    struct server *server, int *index);
