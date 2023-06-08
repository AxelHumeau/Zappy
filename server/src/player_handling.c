/*
** EPITECH PROJECT, 2023
** player_handling.c
** File description:
** player_handling
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "macro.h"

static int accept_player_team(struct server *server,
    struct client_entry *entry, char *line, int i)
{
    char *info = NULL;
    int slot_left = server->teams[i].nb_slots_left;

    if (!strcmp(server->teams[i].name, line) && slot_left != 0) {
        server->teams[i].nb_slots_left--;
        asprintf(&info, "%d\n%d %d\n", server->teams[i].nb_slots_left,
            server->width, server->height);
        add_to_buffer(&entry->buf_to_send, info, strlen(info));
        write_buffer(&entry->buf_to_send, entry->fd);
        SLIST_INSERT_HEAD(&server->teams[i].players, entry, next);
        free(info);
        free(line);
        return EXIT_SUCCESS;
    }
    return EXIT_FAIL;
}

static int accept_player_connexion(struct client_entry *entry)
{
    int read_char = 0;
    char buffer[MAX_SIZE_BUFFER];

    add_to_buffer(&entry->buf_to_send, WELCOME, strlen(WELCOME));
    if (write_buffer(&entry->buf_to_send, entry->fd) != EXIT_SUCCESS)
        return EXIT_FAIL;
    read_char = read(entry->fd, buffer, MAX_SIZE_BUFFER);
    if (read_char <= 0)
        return EXIT_FAIL;
    add_to_buffer(&entry->buf_to_recv, buffer, read_char);
    return EXIT_SUCCESS;
}

int put_player_team(struct server *server, struct client_entry *entry)
{
    char *line = NULL;

    if (accept_player_connexion(entry) != EXIT_SUCCESS)
        return EXIT_FAIL;
    line = get_line_in_buffer(&entry->buf_to_recv);
    for (size_t i = 0; i < server->nb_teams; i++) {
        if (accept_player_team(server, entry, line, i) == EXIT_SUCCESS)
            return EXIT_SUCCESS;
    }
    add_to_buffer(&entry->buf_to_send, KO, strlen(KO));
    write_buffer(&entry->buf_to_send, entry->fd);
    free(line);
    return EXIT_FAIL;
}
