/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tab
*/

#pragma once

#include "gui/commands.h"

#define NB_GUI_COMMANDS (sizeof(GUI_COMMANDS) / sizeof(*GUI_COMMANDS))

typedef struct gui_command_pair {
    char *name;
    gui_command_t *command;
} gui_command_pair_t;

static const gui_command_pair_t GUI_COMMANDS[] = {
    {"msz", &send_map_size},
    {"bct", &send_tile_content},
    {"mct", &send_map_content},
    {"tna", &send_team_names},
    {"ppo", &send_player_pos},
    {"plv", &send_player_level},
    {"pin", &send_player_inventory},
    {"sgt", &send_time_request},
    {"sst", &send_time_modification},
};
