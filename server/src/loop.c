/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** loop
*/

#include "server.h"
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/select.h>
#include <sys/param.h>
#include <unistd.h>

static bool have_to_stop(struct server *server)
{
    struct signalfd_siginfo siginfo;

    if (read(server->sig_fd, &siginfo, sizeof(siginfo)) != sizeof(siginfo))
        return false;
    return siginfo.ssi_signo == SIGINT;
}

static int set_fds(struct server *server, fd_set *read_fds)
{
    int maxfd = 0;
    struct client_entry *client;

    FD_ZERO(read_fds);
    FD_SET(server->listening_fd, read_fds);
    maxfd = MAX(maxfd, server->listening_fd);
    FD_SET(server->sig_fd, read_fds);
    maxfd = MAX(maxfd, server->sig_fd);
    SLIST_FOREACH(client, &server->clients, next) {
        FD_SET(client->fd, read_fds);
        maxfd = MAX(maxfd, client->fd);
    }
    return maxfd + 1;
}

static void loop_through_clients(struct server *server, fd_set *readfds)
{
    struct client_entry *client;

    SLIST_FOREACH(client, &server->clients, next)
        if (handle_client(client, server, readfds)) {
            FD_CLR(client->fd, readfds);
            SLIST_REMOVE(&server->clients, client, client_entry, next);
            destroy_client(client);
            return loop_through_clients(server, readfds);
        }
}

int loop(struct server *server)
{
    fd_set readfds;

    while (!server->stopped && select(set_fds(server, &readfds),
        &readfds, NULL, NULL, NULL) >= 0) {
        if (FD_ISSET(server->sig_fd, &readfds) && have_to_stop(server))
            break;
        if (FD_ISSET(server->listening_fd, &readfds))
            accept_client(server);
        loop_through_clients(server, &readfds);
    }
    destroy_server(server);
    return 0;
}
