/*
** EPITECH PROJECT, 2023
** macro.h
** File description:
** macro
*/

#ifndef MACRO_H_
    #define MACRO_H_

    #include "server.h"
    #define KO "ko\n"
    #define OK "ok\n"
    #define WELCOME "WELCOME\n"
    #define GRAPHIC "GRAPHIC"
    #define NB_DIRECTIONS 4
    #define MAX_COMMAND_PLAYER 12

enum resource;

static const int EXIT_FAIL = -1;
static const int EXIT_ERROR = 84;
static const size_t MAX_SIZE_BUFFER = 256;
static const int MAX_PORT_NUMBER = 65535;
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

#endif /* !MACRO_H_ */
