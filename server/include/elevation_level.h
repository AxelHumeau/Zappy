/*
** EPITECH PROJECT, 2023
** elevation_level.h
** File description:
** elevation_level
*/

#ifndef ELEVATION_LEVEL_H_
    #define ELEVATION_LEVEL_H_

    #include "macro.h"

/// @brief Elevation struct
typedef struct elevation {
    int level;
    int nb_players;
    size_t resource[NB_RESOURCES];
} elevation_t;

/// @brief ELEVATION struct condition
static const elevation_t elevation_ritual[NB_LEVEL] = {
    {1, 1, {0, 1, 0, 0, 0, 0, 0}},
    {2, 2, {0, 1, 1, 1, 0, 0, 0}},
    {3, 2, {0, 2, 0, 1, 0, 2, 0}},
    {4, 4, {0, 1, 1, 2, 0, 1, 0}},
    {6, 4, {0, 1, 2, 1, 3, 0, 0}},
    {6, 6, {0, 1, 2, 3, 0, 1, 0}},
    {7, 6, {2, 2, 2, 2, 2, 2, 1}}
};

#endif /* !ELEVATION_LEVEL_H_ */
