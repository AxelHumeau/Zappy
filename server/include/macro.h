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
    #define NB_DIRECTIONS 4
    #define NB_COMMAND_PLAYER 12
    #define MAX_COMMAND_SIZE 10
    #define ZONE_SIZE 8
    #define ABS(x) (((x) < 0 ? (-x) : (x)))
    #include "server.h"

enum resource;
struct position;

static const int EXIT_FAIL = -1;
static const int PORTION_REFILL = 5;
static const int EXIT_ERROR = 84;
static const size_t MAX_SIZE_BUFFER = 256;
static const int MAX_PORT_NUMBER = 65535;
static const int REFILL_TIME = 20;
static const int FOOD_TIME = 126;
static const double DENSITY[NB_RESOURCES] = {
    [FOOD] = 0.5,
    [LINEMATE] = 0.3,
    [DERAUMERE] = 0.15,
    [SIBUR] = 0.1,
    [MENDIANE] = 0.1,
    [PHIRAS] = 0.08,
    [THYSMANE] = 0.05,
};
static const char * const RESSOURCE_STR[NB_RESOURCES] = {
    [FOOD] = "food",
    [LINEMATE] = "linemate",
    [DERAUMERE] = "deraumere",
    [SIBUR] = "sibur",
    [MENDIANE] = "mendiane",
    [PHIRAS] = "phiras",
    [THYSMANE] = "thysmane",
};
static const int DIRECTION[4][2] = {
    [UP] = {0, -1},
    [RIGHT] = {1, 0},
    [DOWN] = {0, 1},
    [LEFT] = {-1, 0},
};
static const char * const DIRECTION_STR[NB_DIRECTIONS] = {
    [UP] = "up",
    [RIGHT] = "right",
    [DOWN] = "down",
    [LEFT] = "left",
};
static const int POS_LOOK[4] = {
    [UP] = -1,
    [RIGHT] = -1,
    [DOWN] = 1,
    [LEFT] = 1
};
static const int DIRECTION_ZONE[4] = {
    [UP] = 1,
    [RIGHT] = 3,
    [DOWN] = 5,
    [LEFT] = 7,
};
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
