/*
** EPITECH PROJECT, 2023
** utils.c
** File description:
** utils
*/

#include <stdlib.h>
#include <stdio.h>
#include "macro.h"

int find_power_of_base(int nb, int base)
{
    int power = 0;

    while (nb != 0)
        nb /= base;
    return power;
}

int display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ");
    printf("... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unitfor execution of actions");
    printf("\n");
    return EXIT_SUCCESS;
}

static void display_elem_map(struct server server, int x, int y)
{
    for (int i = 0; i < NB_RESOURCES; i++) {
        for (size_t size = 0; size < server.maps[y][x].resources[i]; size++)
            printf("%s, ", RESSOURCE_STR[i]);
    }
}

void display_map(struct server server)
{
    for (int y = 0; y < server.height; y++) {
        for (int x = 0; x < server.width; x++) {
            printf("[");
            display_elem_map(server, x, y);
            printf("]\n");
        }
    }
}
