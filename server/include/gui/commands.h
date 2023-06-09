/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gui_commands
*/

#pragma once

#include "server.h"

typedef int (gui_command_t)(char **, struct server *, struct client_entry *);

gui_command_t map_size;
gui_command_t tile_content;
gui_command_t map_content;
