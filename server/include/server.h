/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** server_struct
*/

#pragma once

#include <sys/queue.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdlib.h>
#include "buffering.h"

/// @brief Node of a client linked list
struct client_entry {
    int id;
    int fd;
    buffer_t buf_to_send;
    buffer_t buf_to_recv;
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

int setup_server(struct server *server);
void destroy_server(struct server *server);

int loop(struct server *server);

void accept_client(struct server *server);
int handle_client(struct client_entry *client,
    struct server *server, fd_set *read_fds);
void destroy_client(struct client_entry *client);
void destroy_clients(struct server *server);
