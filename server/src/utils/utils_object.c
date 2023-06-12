/*
** EPITECH PROJECT, 2023
** utils_object.c
** File description:
** utils_object
*/

#include <string.h>
#include <stddef.h>
#include "macro.h"

bool is_object(char *object)
{
    int is_object = -1;

    for (int i = 0; i < NB_RESOURCES; i++) {
        if (!strcmp(RESSOURCE_STR[i], object))
            is_object = i;
    }
    return is_object;
}
