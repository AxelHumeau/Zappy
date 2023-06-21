/*
** EPITECH PROJECT, 2023
** utils_lists.c
** File description:
** utils_list
*/

#include "macro.h"

int *get_list_ids(struct client_entry **list_players, int size)
{
    int *list_ids = NULL;
    int index = 0;

    if (size == 0)
        return NULL;
    list_ids = malloc(sizeof(int) * size);
    for (int i = 1; list_players[i] != NULL; i++) {
        list_ids[index] = list_players[i]->id;
        index++;
    }
    return list_ids;
}

int list_ids_size(struct client_entry **list_players)
{
    int size = 0;

    for (int i = 1; list_players[i] != NULL; i++)
        size++;
    return size;
}
