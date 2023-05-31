/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** handle_client
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"
#include "macro.h"

void accept_client(struct server *server)
{
    int fd;
    struct client_entry *entry;
    static int count = 0;

    fd = accept(server->listening_fd, NULL, NULL);
    if (fd < 0)
        return;
    entry = malloc(sizeof(struct client_entry));
    entry->fd = fd;
    entry->id = count++;
    entry->is_gui = false;
    init_buffer(&entry->buf_to_send);
    init_buffer(&entry->buf_to_recv);
    SLIST_INSERT_HEAD(&server->clients, entry, next);
}

static void handle_lines(struct client_entry *client, struct server *server)
{
    char *line;

    line = get_line_in_buffer(&client->buf_to_recv);
    while (line != NULL) {
        printf("[client %d]: %s\n", client->id, line);
        free(line);
        line = get_line_in_buffer(&client->buf_to_recv);
    }
}

int handle_client(struct client_entry *client,
    struct server *server, fd_set *read_fds)
{
    char buffer[MAX_SIZE_BUFFER];
    int read_char = 0;

    if (!FD_ISSET(client->fd, read_fds))
        return 0;
    read_char = read(client->fd, buffer, MAX_SIZE_BUFFER);
    if (read_char <= 0)
        return 1;
    add_to_buffer(&client->buf_to_recv, buffer, read_char);
    handle_lines(client, server);
    return 0;
}

void destroy_client(struct client_entry *client)
{
    close(client->fd);
    destroy_buffer(&client->buf_to_send);
    destroy_buffer(&client->buf_to_recv);
    free(client);
}

void destroy_clients(struct server *server)
{
    struct client_entry *tmp = NULL;

    for (struct client_entry *client = server->clients.slh_first; client;) {
        tmp = client->next.sle_next;
        destroy_client(client);
        client = tmp;
    }
}
