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
#include "macro.h"

struct egg;

/// @brief Node of a client linked list
struct client_entry {
    int id;
    int fd;
    buffer_t buf_to_send;
    buffer_t buf_to_recv;
    char *command[MAX_COMMAND_SIZE];
    int count_command;
    bool is_role_defined;
    bool is_gui;
    bool is_dead;
    player_t *player_info;
    int timer;
    long food_time;
    bool laying_egg;
    bool ritual;
    struct egg *egg;
    SLIST_ENTRY(client_entry) next;
};

SLIST_HEAD(clients, client_entry);
SLIST_HEAD(eggs, egg);

/// @brief Server struct
struct server {
    int listening_fd;
    int sig_fd;
    int width;
    int height;
    int port;
    int freq;
    struct team *teams;
    int nb_teams;
    struct tile **maps;
    int ref_resource[NB_RESOURCES];
    int map_resource[NB_RESOURCES];
    size_t multiplier_resource;
    int max_players_per_team;
    int nb_players;
    struct eggs list_eggs;
    struct clients clients;
    long timestamp;
    long resources_time;
    int id_egg;
    int timerfd;
};

struct team {
    char *name;
    int nb_slots_left;
    struct clients players;
};

// Destroy_server.c
int setup_server(struct server *server);
void destroy_server(struct server *server);
void destroy_player(struct client_entry *client, struct server *server);

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
int is_object(char *object);

// Utils_broadcast.c
void debug_map_broadcast(struct client_entry *client,
    struct client_entry *player, struct position zone[]);

// Utils_look.c
char *add_tiles_elem_string(struct server *server, struct client_entry *client,
    struct position pos, char *look_info);

// Utils_player.c
bool is_player(struct client_entry *player, struct client_entry *client);
void display_player(struct server *server);
bool same_pos(struct client_entry *player, struct client_entry *client);
void init_entry(struct client_entry *entry);
void set_position_player(struct server *server, player_t *info,
    struct team *team);

// Utils_end_game.c
bool end_game(struct server *server);

// Utils_list.c
int list_ids_size(struct client_entry **list_players);
int *get_list_ids(struct client_entry **list_players, int size);

// Utils_incantation.c
struct client_entry **condition_ritual(struct client_entry *client,
    struct server *server);
void send_ritual_message(struct client_entry *client,
    struct client_entry **list, bool is_elevate);

// Str_to_array.c
char **str_to_array(char *str, char *separator);
void free_array(char **array);

// Init_game.c
int init_game(struct server *server);

// Init_resource.c
void refill_resources(struct server *server);
void set_resource_map(struct server *server);

// player_handling.c
int put_client_team(struct server *server, struct client_entry *entry,
    char *line);
void handle_player_timer(struct server *server);

// command_handling.c
int exec_command(struct client_entry *client,
    struct server *server, char *line);

// Player/player_command.c
void handle_player_command(struct client_entry *client, char *line);
void exec_player_command(struct client_entry *client,
    struct server *server, char *line);

// handle_gui_client.c
int handle_gui(struct client_entry *client, struct server *server, char *line);

// init_gui_client.c
int init_gui_client(struct server *server, struct client_entry *client);

// check_instant_command.c
void check_incantation(struct client_entry *client, struct server *server,
    char *line);
void check_fork(struct client_entry *client, struct server *server,
    char *line);
