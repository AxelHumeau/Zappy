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

/// @brief Team struct
struct team {
    char *name;
    int nb_slots_left;
    struct clients players;
};

// Destroy_server.c
/**
 * @brief Set the up server object
 * @param server
 * @return int
 */
int setup_server(struct server *server);

/**
 * @brief destroy the server
 * @param server
 */
void destroy_server(struct server *server);

/**
 * @brief destroy player from the team
 * @param client
 * @param server
 */
void destroy_player(struct client_entry *client, struct server *server);

/**
 * @brief main loop
 * @param server
 * @return int
 */
int loop(struct server *server);

/**
 * @brief Accept client and set informations
 * @param server
 */
void accept_client(struct server *server);

/**
 * @brief Handle client function (alive, read ok...)
 * @param client
 * @param server
 * @param read_fds
 * @return int
 */
int handle_client(struct client_entry *client,
    struct server *server, fd_set *read_fds);

/**
 * @brief destroy client and free all information
 * @param client
 */
void destroy_client(struct client_entry *client);
/**
 * @brief Function that loop on all the clients and destroy it
 * @param server
 */
void destroy_clients(struct server *server);

// Utils.c
/**
 * @brief Display help
 * @return int
 */
int display_help(void);
/**
 * @brief display map utils
 * @param server
 */
void display_map(struct server server);
/**
 * @brief concat information string to send to player
 * @param src
 * @param value
 * @param space
 * @return char *
 */
char *concat_info_string(char *src, const char *value, bool space);
/**
 * @brief Find power of base
 * @param nb
 * @param base
 * @return int
 */
int find_power_of_base(int nb, int base);

// Utils_object.c
/**
 * @brief Check if a object as string is a existing object
 * @param object
 * @return int
 */
int is_object(char *object);

// Utils_broadcast.c
/**
 * @brief Utils to check information about the broadcast
 * @param client
 * @param player
 * @param zone
 */
void debug_map_broadcast(struct client_entry *client,
    struct client_entry *player, struct position zone[]);

// Utils_look.c
/**
 * @brief Add element in the tiles to the message for the look command
 * @param server
 * @param client
 * @param pos
 * @param look_info
 * @return char*
 */
char *add_tiles_elem_string(struct server *server, struct client_entry *client,
    struct position pos, char *look_info);

// Utils_player.c
/**
 * @brief Check if a client_entry is a player
 * @param player
 * @param client
 * @return true
 * @return false
 */
bool is_player(struct client_entry *player, struct client_entry *client);
/**
 * @brief Utils to display the player on the map
 * @param server
 */
void display_player(struct server *server);
/**
 * @brief Check if two player in the same position
 * @param player
 * @param client
 * @return true
 * @return false
 */
bool same_pos(struct client_entry *player, struct client_entry *client);
/**
 * @brief Init information about a entry with basic value
 * @param entry
 */
void init_entry(struct client_entry *entry);
/**
 * @brief Set the position player object
 * @param server
 * @param info
 * @param team
 */
void set_position_player(struct server *server, player_t *info,
    struct team *team);

// Utils_end_game.c
/**
 * @brief Check end game condition
 * @param server
 * @return true
 * @return false
 */
bool end_game(struct server *server);

// Utils_list.c

/**
 * @brief Get list ids size of all players participate in an incantation
 * @param list_players
 * @return int
 */
int list_ids_size(struct client_entry **list_players);

/**
 * @brief Get list ids of all players participate in an incantation
 * @param list_players
 * @return int
 */
int *get_list_ids(struct client_entry **list_players, int size);

// Utils_incantation.c
/**
 * @brief Condition for the ritual
 * @param client
 * @param server
 * @return struct client_entry**
 */
struct client_entry **condition_ritual(struct client_entry *client,
    struct server *server);
/**
 * @brief send ritual message (if success or not)
 * @param client
 * @param list
 * @param is_elevate
 */
void send_ritual_message(struct client_entry *client,
    struct client_entry **list, bool is_elevate);

// Str_to_array.c
/**
 * @brief Str to word array
 * @param str
 * @param separator
 * @return char**
 */
char **str_to_array(char *str, char *separator);
/**
 * @brief Free array
 * @param array
 */
void free_array(char **array);

// Init_game.c
/**
 * @brief Init game function
 * @param server
 * @return int
 */
int init_game(struct server *server);

// Init_resource.c
/**
 * @brief Refill resources needed in the map
 * @param server
 */
void refill_resources(struct server *server);
/**
 * @brief Set the resource map object
 * @param server
 */
void set_resource_map(struct server *server);

// player_handling.c
/**
 * @brief Put client to team
 * @param server
 * @param entry
 * @param line
 * @return int
 */
int put_client_team(struct server *server, struct client_entry *entry,
    char *line);
/**
 * @brief Handle player timer to execute a command
 * @param server
 */
void handle_player_timer(struct server *server);

// Player/player_command.c
/**
 * @brief Handle player command, check if it exists or not
 * @param client
 * @param line
 */
void handle_player_command(struct client_entry *client, char *line);
/**
 * @brief Exec player command after the timer is good
 * @param client
 * @param server
 * @param line
 */
void exec_player_command(struct client_entry *client,
    struct server *server, char *line);

// handle_gui_client.c
/**
 * @brief Handle gui command
 * @param client
 * @param server
 * @param line
 * @return int
 */
int handle_gui(struct client_entry *client, struct server *server, char *line);

// init_gui_client.c
/**
 * @brief Init gui client
 * @param server
 * @param client
 * @return int
 */
int init_gui_client(struct server *server, struct client_entry *client);

// check_instant_command.c
/**
 * @brief Check if possible incantation
 * @param client
 * @param server
 * @param line
 */
void check_incantation(struct client_entry *client, struct server *server,
    char *line);
/**
 * @brief Check if possible fork
 * @param client
 * @param server
 * @param line
 */
void check_fork(struct client_entry *client, struct server *server,
    char *line);
