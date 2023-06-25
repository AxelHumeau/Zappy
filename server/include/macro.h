/*
** EPITECH PROJECT, 2023
** macro.h
** File description:
** macro
*/

#ifndef MACRO_H_
    #define MACRO_H_

    #define KO "ko\n"
    #define OK "ok\n"
    #define WELCOME "WELCOME\n"
    #define GRAPHIC "GRAPHIC"
    #define ELEVATION "Elevation underway\n"
    #define DEAD "dead\n"
    #define NB_DIRECTIONS 4
    #define NB_COMMAND_PLAYER 12
    #define MAX_COMMAND_SIZE 10
    #define NB_LEVEL 7
    #define ZONE_SIZE 8
    #define INCANTATION "Incantation"
    #define FORK "Fork"
    #define ABS(x) (((x) < 0 ? (-x) : (x)))
    #include "server.h"

enum resource;
struct position;

static const int MAX_LEVEL = 8;
static const int NB_PLAYER_LEVEL_MAX = 6;
static const int EXIT_FAIL = -1;
static const int PORTION_REFILL = 5;
static const int EXIT_ERROR = 84;
static const size_t MAX_SIZE_BUFFER = 256;
static const int MAX_PORT_NUMBER = 65535;
static const int REFILL_TIME = 20;
static const int FOOD_TIME = 126;
static const long FOOD_PLAYER = 10;

static const int TIMER_CLASSIC = 7;
static const int TIMER_FAST = 1;
static const int NO_TIMER = 0;
static const int TIMER_FORK = 42;
static const int TIMER_INCANTATION = 300;

/// @brief MACRO Densitry associated enum RESOURCES to a VALUE
static const double DENSITY[NB_RESOURCES] = {
    [FOOD] = 0.5,
    [LINEMATE] = 0.3,
    [DERAUMERE] = 0.15,
    [SIBUR] = 0.1,
    [MENDIANE] = 0.1,
    [PHIRAS] = 0.08,
    [THYSMANE] = 0.05,
};

/// @brief MACRO RESSOURCE_STR associated enum RESOURCES to its STRING
static const char * const RESSOURCE_STR[NB_RESOURCES] = {
    [FOOD] = "food",
    [LINEMATE] = "linemate",
    [DERAUMERE] = "deraumere",
    [SIBUR] = "sibur",
    [MENDIANE] = "mendiane",
    [PHIRAS] = "phiras",
    [THYSMANE] = "thysmane",
};

/// @brief MACRO DIRECTION associated enum DIRECTION to VECTOR
static const int DIRECTION[NB_DIRECTIONS][2] = {
    [UP] = {0, -1},
    [RIGHT] = {1, 0},
    [DOWN] = {0, 1},
    [LEFT] = {-1, 0},
};

/// @brief MACRO DIRECTION associated enum DIRECTION to its STRING
static const char * const DIRECTION_STR[NB_DIRECTIONS] = {
    [UP] = "up",
    [RIGHT] = "right",
    [DOWN] = "down",
    [LEFT] = "left",
};

/// @brief MACRO POS_LOOK associated enum DIRECTION to a VALUE for the LOOK
static const int POS_LOOK[NB_DIRECTIONS] = {
    [UP] = -1,
    [RIGHT] = -1,
    [DOWN] = 1,
    [LEFT] = 1
};

/// @brief MACRO DIRECTION_ZONE associated to DIRECTION to a
///        DIRECTION_INDEX to the UP
static const int DIRECTION_ZONE[NB_DIRECTIONS] = {
    [UP] = 1,
    [RIGHT] = 3,
    [DOWN] = 5,
    [LEFT] = 7,
};

/// @brief MACRO ZONE_INDEX associated to position for the zone
///        around the player
static const struct position ZONE_INDEX[ZONE_SIZE] = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
};

#endif /* !MACRO_H_ */
