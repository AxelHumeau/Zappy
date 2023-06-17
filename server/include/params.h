/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** params
*/

#pragma once

#include "server.h"

int get_server_params(char **params, int nb_params, struct server *server);
int get_port_and_team_name(char **params, int nb_params,
    struct server *server, int *index);
int get_dimensions_freq_nb_client(char **params, int nb_params,
    struct server *server, int *index);
void set_teams(struct server *server, char **teams);
