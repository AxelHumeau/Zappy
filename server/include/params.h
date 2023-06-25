/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** params
*/

#pragma once

#include "server.h"

/**
 * @brief Get the server params object
 * @param params
 * @param nb_params
 * @param server
 * @return int
 */
int get_server_params(char **params, int nb_params, struct server *server);
/**
 * @brief Get the port and team name object
 * @param params
 * @param nb_params
 * @param server
 * @param index
 * @return int
 */
int get_port_and_team_name(char **params, int nb_params,
    struct server *server, int *index);
/**
 * @brief Get the dimensions freq nb client object
 * @param params
 * @param nb_params
 * @param server
 * @param index
 * @return int
 */
int get_dimensions_freq_nb_client(char **params, int nb_params,
    struct server *server, int *index);
/**
 * @brief Set the teams object
 * @param server
 * @param teams
 */
void set_teams(struct server *server, char **teams);
