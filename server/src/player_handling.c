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

static void set_info_player(struct client_entry *entry, struct server *server,
    struct team *team)
{
    entry->player_info.x = rand() % server->width;
    entry->player_info.y = rand() % server->height;
    memset(entry->player_info.inventory, 0,
        sizeof(entry->player_info.inventory));
    entry->player_info.inventory[0] = 10;
    entry->player_info.level = 1;
    entry->player_info.time_units_left = 10;
    entry->player_info.team = team;
    entry->player_info.last_action = 0;
    entry->player_info.direction = rand() % NB_DIRECTIONS;
}

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
        set_info_player(entry, server, &server->teams[i]);
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

int is_graphic_client(struct client_entry *entry, char *line)
{
    if (!strcmp(line, GRAPHIC)) {
        free(line);
        return EXIT_SUCCESS;
    }
    return EXIT_FAIL;
}

int put_client_team(struct server *server, struct client_entry *entry)
{
    char *line = NULL;

    if (accept_player_connexion(entry) != EXIT_SUCCESS)
        return EXIT_FAIL;
    line = get_line_in_buffer(&entry->buf_to_recv);
    if (is_graphic_client(entry, line) == EXIT_SUCCESS)
        return EXIT_SUCCESS;
    for (size_t i = 0; i < server->nb_teams; i++) {
        if (accept_player_team(server, entry, line, i) == EXIT_SUCCESS)
            return EXIT_SUCCESS;
    }
    add_to_buffer(&entry->buf_to_send, KO, strlen(KO));
    write_buffer(&entry->buf_to_send, entry->fd);
    free(line);
    return EXIT_FAIL;
}
