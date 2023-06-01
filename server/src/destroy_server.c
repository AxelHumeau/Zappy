/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** destroy_server
*/

#include "server.h"
#include <unistd.h>

void destroy_server(struct server *server)
{
    free(server->teams);
    destroy_clients(server);
    close(server->listening_fd);
    close(server->sig_fd);
}
