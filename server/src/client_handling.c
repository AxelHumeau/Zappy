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
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "macro.h"
#include "gui/events.h"

void accept_client(struct server *server)
{
    struct client_entry *entry = NULL;
    static int count = 0;
    int fd = accept(server->listening_fd, NULL, NULL);

    if (fd < 0)
        return;
    entry = malloc(sizeof(struct client_entry));
    entry->fd = fd;
    entry->id = count++;
    init_entry(entry);
    init_buffer(&entry->buf_to_send);
    init_buffer(&entry->buf_to_recv);
    add_to_buffer(&entry->buf_to_send, WELCOME, strlen(WELCOME));
    SLIST_INSERT_HEAD(&server->clients, entry, next);
}

static void handle_lines(struct client_entry *client, struct server *server)
{
    char *line;

    line = get_line_in_buffer(&client->buf_to_recv);
    while (line != NULL) {
        if (client->is_gui)
            handle_gui(client, server, line);
        else
            handle_player_command(client, line);
        free(line);
        line = get_line_in_buffer(&client->buf_to_recv);
    }
}

int handle_client(struct client_entry *client,
    struct server *server, fd_set *read_fds)
{
    char buffer[MAX_SIZE_BUFFER];
    int read_char = 0;

    if (client->is_dead)
        return EXIT_FAIL;
    if (client->is_role_defined && !client->is_gui &&
        client->player_info->inventory[FOOD] == 0) {
            client->is_dead = true;
            add_to_buffer(&client->buf_to_send, DEAD, strlen(DEAD));
    }
    if (!FD_ISSET(client->fd, read_fds))
        return EXIT_SUCCESS;
    read_char = read(client->fd, buffer, MAX_SIZE_BUFFER);
    if (read_char <= 0)
        return EXIT_FAIL;
    add_to_buffer(&client->buf_to_recv, buffer, read_char);
    if (!client->is_role_defined)
        return put_client_team(server, client);
    handle_lines(client, server);
    return EXIT_SUCCESS;
}

void destroy_client(struct client_entry *client, struct server *server)
{
    if (client->is_role_defined && !client->is_gui)
        client->player_info->team->nb_slots_left++;
    if (client->is_role_defined && !client->is_gui) {
        broadcast_to_guis(server, &notify_death, client->id);
        free(client->player_info);
        for (int i = 0; i < client->count_command; i++)
            free(client->command[i]);
    }
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
        destroy_client(client, server);
        client = tmp;
    }
}
