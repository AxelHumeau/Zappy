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
    struct client_entry *copy = NULL;

    if (!strcmp(server->teams[i].name, line) && slot_left != 0) {
        server->teams[i].nb_slots_left--;
        asprintf(&info, "%d\n%d %d\n", server->teams[i].nb_slots_left,
            server->width, server->height);
        add_to_buffer(&entry->buf_to_send, info, strlen(info));
        copy = malloc(sizeof(struct client_entry));
        memcpy(copy, entry, sizeof(struct client_entry));
        SLIST_INSERT_HEAD(&server->teams[i].players, copy, next);
        entry->player.team = &server->teams[i];
        entry->player.orientation = rand() % 4 + 1;
        free(info);
        free(line);
        entry->is_role_defined = true;
        return EXIT_SUCCESS;
    }
    return EXIT_FAIL;
}

int is_graphic_client(struct client_entry *entry, char *line)
{
    if (!strcmp(line, GRAPHIC)) {
        entry->is_gui = true;
        free(line);
        entry->is_role_defined = true;
        return EXIT_SUCCESS;
    }
    return EXIT_FAIL;
}

int put_client_team(struct server *server, struct client_entry *entry)
{
    char *line = NULL;

    line = get_line_in_buffer(&entry->buf_to_recv);
    if (is_graphic_client(entry, line) == EXIT_SUCCESS) {
        init_gui_client(server, entry);
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; i < server->nb_teams; i++) {
        if (accept_player_team(server, entry, line, i) == EXIT_SUCCESS)
            return EXIT_SUCCESS;
    }
    add_to_buffer(&entry->buf_to_send, KO, strlen(KO));
    free(line);
    return EXIT_FAIL;
}
