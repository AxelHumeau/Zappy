/*
** EPITECH PROJECT, 2023
** inventory.c
** File description:
** inventory
*/

#include <string.h>
#include <stdio.h>
#include "macro.h"

static char *set_inventory_message(struct client_entry *client)
{
    char *inventory = NULL;
    size_t info[NB_RESOURCES];

    memcpy(&info, client->player_info.inventory, sizeof(size_t[NB_RESOURCES]));
    asprintf(&inventory,
        "[ %s %ld, %s %ld, %s %ld, %s %ld, %s %ld, %s %ld, %s %ld ]\n",
        RESSOURCE_STR[0], info[0], RESSOURCE_STR[1], info[1],
        RESSOURCE_STR[2], info[2], RESSOURCE_STR[3], info[3],
        RESSOURCE_STR[4], info[4], RESSOURCE_STR[5], info[5],
        RESSOURCE_STR[6], info[6]);
    return inventory;
}

void inventory(char **cmd, struct client_entry *client, struct server *)
{
    char *inventory = NULL;

    if (cmd[1] == NULL) {
        inventory = set_inventory_message(client);
        add_to_buffer(&client->buf_to_send, inventory, strlen(inventory));
        free(inventory);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
