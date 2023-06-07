/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** game
*/

#pragma once

#include <stdlib.h>

struct team;

#define NB_RESOURCES 7

enum resource {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSMANE,
};

typedef struct player {
    int x;
    int y;
    size_t inventory[NB_RESOURCES];
    size_t level;
    size_t time_units_left;
    time_t last_action;
    struct team *team;
} player_t;

struct tile {
    size_t nb_ressources;
    enum resource *resources;
    int x;
    int y;
};
