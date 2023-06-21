/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gui_commands
*/

#pragma once

#include "server.h"

typedef int (gui_command_t)(char **, struct server *, struct client_entry *);

gui_command_t send_map_size;
gui_command_t send_tile_content;
gui_command_t send_map_content;
gui_command_t send_team_names;
gui_command_t send_player_pos;
gui_command_t send_player_level;
gui_command_t send_player_inventory;
gui_command_t send_time_request;
gui_command_t send_time_modification;
