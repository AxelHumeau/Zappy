/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** setup_connexion
*/

#include <signal.h>
#include <sys/select.h>
#include <sys/signalfd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "server.h"

int setup_server(struct server *server)
{
    sigset_t mask;
    struct sockaddr_in ad;

    SLIST_INIT(&server->clients);
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    server->sig_fd = signalfd(-1, &mask, O_CLOEXEC);
    server->listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    ad.sin_family = AF_INET;
    ad.sin_port = htons(server->port);
    ad.sin_addr.s_addr = INADDR_ANY;
    if (server->listening_fd < 0 ||
        bind(server->listening_fd, (struct sockaddr *) &ad, sizeof(ad)) != 0 ||
        listen(server->listening_fd, FD_SETSIZE - 1) != 0)
        return 1;
    return 0;
}
