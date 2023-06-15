/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** loop
*/

#include <signal.h>
#include <sys/signalfd.h>
#include <sys/select.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "macro.h"

static bool have_to_stop(struct server *server)
{
    struct signalfd_siginfo siginfo;

    if (read(server->sig_fd, &siginfo, sizeof(siginfo)) != sizeof(siginfo))
        return false;
    return siginfo.ssi_signo == SIGINT;
}

static int set_fds(struct server *server, fd_set *read_fds, fd_set *write_fds)
{
    int maxfd = 0;
    struct client_entry *client;

    FD_ZERO(write_fds);
    FD_ZERO(read_fds);
    FD_SET(server->listening_fd, read_fds);
    maxfd = MAX(maxfd, server->listening_fd);
    FD_SET(server->sig_fd, read_fds);
    maxfd = MAX(maxfd, server->sig_fd);
    FD_SET(server->timerfd, read_fds);
    maxfd = MAX(maxfd, server->timerfd);
    SLIST_FOREACH(client, &server->clients, next) {
        FD_SET(client->fd, read_fds);
        FD_SET(client->fd, write_fds);
        maxfd = MAX(maxfd, client->fd);
    }
    return maxfd + 1;
}

static void loop_through_clients(struct server *server, fd_set *readfds,
    fd_set *writefds)
{
    struct client_entry *client;

    SLIST_FOREACH(client, &server->clients, next) {
        if (FD_ISSET(client->fd, writefds))
            write_buffer(&client->buf_to_send, client->fd);
        if (handle_client(client, server, readfds)) {
            FD_CLR(client->fd, readfds);
            FD_CLR(client->fd, writefds);
            SLIST_REMOVE(&server->clients, client, client_entry, next);
            destroy_client(client);
            return loop_through_clients(server, readfds, writefds);
        }
    }
}

void timer_command(struct server *server)
{
    long nb = 0;
    struct client_entry *client = NULL;

    read(server->timerfd, &nb, sizeof(long));
    server->timestamp++;
    server->resources_time++;
    if (server->resources_time % 20 == 0) {
        printf("REFIILLL\n");
        server->resources_time = 0;
    }
    SLIST_FOREACH(client, &server->clients, next) {
        if (client->is_role_defined && client->count_command > 0)
            exec_player_command(client, server, client->command[0]);
    }
}

int loop(struct server *server)
{
    fd_set readfds;
    fd_set writefds;

    while (select(set_fds(server, &readfds, &writefds),
        &readfds, &writefds, NULL, NULL) >= 0) {
        if (FD_ISSET(server->timerfd, &readfds))
            timer_command(server);
        if (FD_ISSET(server->sig_fd, &readfds) && have_to_stop(server))
            break;
        if (FD_ISSET(server->listening_fd, &readfds))
            accept_client(server);
        loop_through_clients(server, &readfds, &writefds);
    }
    destroy_server(server);
    return 0;
}
