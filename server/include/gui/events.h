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

int broadcast_to_guis(struct server *server, event_func_t *function, ...);
void send_new_player_str(struct client_entry *client, int player_id,
    player_t *player);

event_func_t notify_new_player;
