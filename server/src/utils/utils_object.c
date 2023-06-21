/*
** EPITECH PROJECT, 2023
** utils_object.c
** File description:
** utils_object
*/

#include <string.h>
#include <stddef.h>
#include "macro.h"

int is_object(char *object)
{
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (!strcmp(RESSOURCE_STR[i], object))
            return i;
    }
    return EXIT_FAIL;
}
