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
    printf("Server: \n"
        "\tport = %d\n"
        "\twidth = %d\n"
        "\theight = %d\n"
        "\tfreq = %d\n"
        "\tmax player per team:%d\n"
        "\tteams: %ld\n", server.port, server.width, server.height, server.freq,
        server.max_players_per_team, server.nb_teams);
    for (size_t i = 0; i < server.nb_teams; i++)
        printf("\t\t%s\n", server.teams[i].name);
    return 0;
}
