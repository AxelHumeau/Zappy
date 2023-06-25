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

/// @brief Enum ressource on the map
enum resource {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSMANE,
};

/// @brief Enum direction for the game
enum direction {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
};

/// @brief structure egg
typedef struct egg {
    int id;
    int x;
    int y;
    struct team *team;
    SLIST_ENTRY(egg) next;
} egg_t;

/// @brief structure position
struct position {
    int x;
    int y;
};

/// @brief structure player
typedef struct player {
    int x;
    int y;
    enum direction direction;
    size_t inventory[NB_RESOURCES];
    int level;
    size_t time_units_left;
    time_t last_action;
    struct team *team;
} player_t;

/// @brief structure tile
struct tile {
    size_t resources[NB_RESOURCES];
    int x;
    int y;
};
