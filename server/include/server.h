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
#include "game.h"

/// @brief Node of a client linked list
struct client_entry {
    int id;
    int fd;
    buffer_t buf_to_send;
    buffer_t buf_to_recv;
    bool is_role_defined;
    bool is_gui;
    player_t player_info;
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
    struct tile **maps;
    int max_players_per_team;
    struct clients clients;
};

struct team {
    char *name;
    /// @brief pointer to the max number of players in the server struct
    int nb_slots_left;
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

// Utils.c
int display_help(void);
void display_map(struct server server);
char *concat_info_string(char *src, const char *value, bool space);
int find_power_of_base(int nb, int base);

// Utils_object.c
bool is_object(char *object);

// Str_to_array.c
char **str_to_array(char *str, char *separator);
void free_array(char **array);

// Init_game.c
int init_game(struct server *server);

// Init_resource.c
void set_resource_map(struct server *server);

// player_handling.c
int put_client_team(struct server *server, struct client_entry *entry);

// command_handling.c
int exec_command(struct client_entry *client,
    struct server *server, char *line);

// Player/player_command.c
void exec_player_command(struct client_entry *client,
    struct server *server, char *line);

// handle_gui_client.c
int handle_gui(struct client_entry *client, struct server *server, char *line);

// init_gui_client.c
int init_gui_client(struct server *server, struct client_entry *client);
