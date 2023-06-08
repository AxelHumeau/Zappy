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
    {"msz", &map_size},
};
