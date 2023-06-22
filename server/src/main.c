/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "params.h"
#include "macro.h"

int main(int argc, char **argv)
{
    struct server server;

    srand(time(NULL));
    if (argc == 2 && !strcmp(argv[1], "-h"))
        return display_help();
    if (argc < 11 || get_server_params(argv, argc, &server) != EXIT_SUCCESS)
        return EXIT_ERROR;
    if (setup_server(&server) != EXIT_SUCCESS)
        return EXIT_ERROR;
    if (init_game(&server) != EXIT_SUCCESS)
        return EXIT_ERROR;
    return loop(&server);
}
