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
#include <stdio.h>
#include <fcntl.h>
#include "server.h"
#include "macro.h"

static void setup_signals(struct server *server)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    server->sig_fd = signalfd(-1, &mask, O_CLOEXEC);
    signal(SIGPIPE, SIG_IGN);
}

int setup_server(struct server *server)
{
    struct sockaddr_in ad;

    SLIST_INIT(&server->clients);
    setup_signals(server);
    server->listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    ad.sin_family = AF_INET;
    ad.sin_port = htons(server->port);
    ad.sin_addr.s_addr = INADDR_ANY;
    if (server->listening_fd < 0 ||
        bind(server->listening_fd, (struct sockaddr *) &ad, sizeof(ad)) != 0 ||
        listen(server->listening_fd, FD_SETSIZE - 1) != 0) {
        dprintf(2, "Non valid port.\n");
        free(server->teams);
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}
