/*
** EPITECH PROJECT, 2023
** utils.c
** File description:
** utils
*/

#include <stdlib.h>
#include <stdio.h>
#include "macro.h"

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
