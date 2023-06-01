/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include "params.h"
#include "macro.h"

int main(int argc, char **argv)
{
    struct server server;

    if (argc == 2 && !strcmp(argv[1], "-h"))
        return display_help();
    if (argc < 13 || get_server_params(argv, argc, &server) != EXIT_SUCCESS)
        return EXIT_ERROR;
    if (setup_server(&server) != EXIT_SUCCESS)
        return EXIT_ERROR;
    return loop(&server);
}
