/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** events
*/

#pragma once

#include "server.h"

int notify_new_player(struct server *server, struct client_entry *client,
    player_t *player, int player_id);
