/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** events
*/

#pragma once

#include "server.h"
#include <stdarg.h>

typedef int event_func_t(struct client_entry *, va_list *);

/// @brief broadcast an event to all connected gui clients
/// @param server server structure
/// @param function to function to broadcast
/// @param ... the arguments to send to the function parameter
/// @return 0 if successful, 1 otherwise
int broadcast_to_guis(struct server *server, event_func_t *function, ...);
void send_new_player_str(struct client_entry *client, int player_id,
    player_t *player);

/** @brief notify when a new player has joined
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the new player, a
 *  player_t * describing the new player
*/
event_func_t notify_new_player;

/** @brief notify when a player have send a message
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player, a
 *  char * describing the message
*/
event_func_t notify_broadcast;

/** @brief notify when a player is laying an egg
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player
*/
event_func_t notify_egg_laying;

/** @brief notify when player expulse
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player
*/
event_func_t notify_expulsion;

/** @brief notify when a player start an incantation
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player, a
 *  player_t * describing the player, the
 *  number of additional players taking part in the incantation, all
 *  the ids of the additionals players, as parameters
*/
event_func_t notify_start_of_incantation;

/** @brief notify when an incantation has ended
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  a player_t * describing the player, an
 *  int describing the success of the incantation (0 or 1)
*/
event_func_t notify_end_of_incantation;

/** @brief notify when a player has dropped a resource
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player, an
 *  int int corresponding to the resource number (refer to enum resource)
*/
event_func_t notify_resource_dropping;

/** @brief notify when a player has collected a resource
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player, an
 *  int int corresponding to the resource number (refer to enum resource)
*/
event_func_t notify_resource_collecting;

/** @brief notify when a player died
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the player
*/
event_func_t notify_death;

/** @brief notify when a egg was layed
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  a egg_t * describing the egg, an
 *  int describing the id of the player who lyed the egg
*/
event_func_t notify_egg_layed;

/** @brief notify when a player connect to an egg
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the egg
*/
event_func_t notify_egg_connection;

/** @brief notify when a egg dies
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  an int describing the id of the egg
*/
event_func_t notify_egg_death;

/** @brief notify when the server send a message to the gui
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  a char * describing the message
*/
event_func_t notify_server_message;

/** @brief notify when the game ended
 * @param client gui client to notify
 *
 * @param args argument list that must contain the following:
 *  a char * describing the team that move
*/
event_func_t notify_end_of_game;
