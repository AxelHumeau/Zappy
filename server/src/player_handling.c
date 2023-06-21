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
#include "gui/events.h"

static void set_info_player(struct client_entry *entry, struct server *server,
    struct team *team)
{
    entry->player_info.x = rand() % server->width;
    entry->player_info.y = rand() % server->height;
    memset(entry->player_info.inventory, 0,
        sizeof(entry->player_info.inventory));
    entry->player_info.inventory[FOOD] = 10;
    entry->player_info.level = 1;
    entry->player_info.time_units_left = 10;
    entry->player_info.team = team;
    entry->player_info.last_action = 0;
    entry->player_info.direction = rand() % NB_DIRECTIONS;
    memset(entry->command, 0, sizeof(char *) * MAX_COMMAND_SIZE);
    entry->count_command = 0;
    entry->is_role_defined = true;
}

static int accept_player_team(struct server *server,
    struct client_entry *entry, char *line, int i)
{
    char *info = NULL;
    int slot_left = server->teams[i].nb_slots_left;
    struct client_entry *copy = NULL;

    if (strcmp(server->teams[i].name, line) || slot_left == 0)
        return EXIT_FAIL;
    server->teams[i].nb_slots_left--;
    asprintf(&info, "%d\n%d %d\n", server->teams[i].nb_slots_left,
        server->width, server->height);
    add_to_buffer(&entry->buf_to_send, info, strlen(info));
    set_info_player(entry, server, &server->teams[i]);
    copy = malloc(sizeof(struct client_entry));
    memcpy(copy, entry, sizeof(struct client_entry));
    SLIST_INSERT_HEAD(&server->teams[i].players, copy, next);
    free(info);
    free(line);
    broadcast_to_guis(server, &notify_new_player,
        entry->id, &entry->player_info);
    server->nb_players++;
    return EXIT_SUCCESS;
}

int is_graphic_client(struct client_entry *entry, char *line)
{
    if (!strcmp(line, GRAPHIC)) {
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
        entry->is_gui = true;
        init_gui_client(server, entry);
        return EXIT_SUCCESS;
    }
    for (int i = 0; i < server->nb_teams; i++) {
        if (accept_player_team(server, entry, line, i) == EXIT_SUCCESS)
            return EXIT_SUCCESS;
    }
    add_to_buffer(&entry->buf_to_send, KO, strlen(KO));
    free(line);
    return EXIT_SUCCESS;
}

void handle_player_timer(struct server *server)
{
    struct client_entry *client = NULL;

    SLIST_FOREACH(client, &server->clients, next) {
        client->food_time++;
        if (client->is_role_defined && !client->is_gui &&
            client->food_time % FOOD_TIME == 0) {
            client->player_info.inventory[FOOD]--;
            client->food_time = 0;
        }
        if (client->is_role_defined && !client->is_gui &&
                client->count_command > 0)
            exec_player_command(client, server, client->command[0]);
    }
}
