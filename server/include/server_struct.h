/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** server_struct
*/

#pragma once

#include <sys/queue.h>
#include <stdbool.h>
#include <stdlib.h>

/// @brief Node of a client linked list
struct client_entry {
    int id;
    int fd;
    bool is_gui;
    SLIST_ENTRY(client_entry) next;
};

SLIST_HEAD(clients, client_entry);

/// @brief Server struct
struct server {
    int listening_fd;
    int sig_fd;
    int width;
    int height;
    int port;
    int freq;
    struct team *teams;
    size_t nb_teams;
    int max_players_per_team;
    struct clients clients;
};

struct team {
    char *name;
    /// @brief pointer to the max number of players in the server struct
    int *max_players;
    size_t num_players;
    struct clients players;
};
