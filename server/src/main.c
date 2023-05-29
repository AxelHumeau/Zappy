/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include "params.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    struct server server;

    if (argc < 13 || get_server_params(argv, argc, &server))
        return 84;
    if (setup_server(&server))
        return 84;
    return loop(&server);
}
