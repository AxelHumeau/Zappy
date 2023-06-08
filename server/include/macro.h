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
    #define WELCOME "WELCOME\n"

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

#endif /* !MACRO_H_ */
