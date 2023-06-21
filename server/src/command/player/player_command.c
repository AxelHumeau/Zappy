/*
** EPITECH PROJECT, 2023
** player_command.c
** File description:
** player_command
*/

#include <string.h>
#include "macro.h"
#include "player_command.h"
#include "gui/events.h"

void handle_player_command(struct client_entry *client, char *line)
{
    if (!strcmp(line, "\0"))
        return;
    if (client->count_command != 10)
        client->command[client->count_command++] = strdup(line);
}

static void clean_player_command(struct client_entry *client)
{
    size_t size = 0;

    free(client->command[0]);
    client->count_command--;
    size = sizeof(char *) * client->count_command;
    memmove(&client->command[0], &client->command[1], size);
}

static void check_incantation(struct client_entry *client,
    struct server *server, char *line)
{
    struct client_entry **list_players = NULL;
    int *list_ids = NULL;
    int size = 0;

    if (!strncmp(line, INCANTATION, strlen(INCANTATION)) && !client->ritual) {
        list_players = condition_ritual(client, server);
        if ((line + strlen(INCANTATION))[0] == '\0' && list_players != NULL) {
            size = list_ids_size(list_players);
            printf("SIZE %d\n", size);
            list_ids = get_list_ids(list_players, size);
            broadcast_to_guis(server, &notify_start_of_incantation,
                client->id, &client->player_info, size, list_ids);
            send_ritual_message(client, list_players, true);
        } else
            add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        client->ritual = true;
    }
    free(list_players);
}

static void time_command(struct client_entry *client,
    struct server *server, char *line, command_t command)
{
    check_incantation(client, server, line);
    if (client->timer == -1)
        client->timer = command.cooldown;
    else if (client->timer <= 0) {
        (command.function) (line + strlen(command.command), client, server);
        display_player(server);
        clean_player_command(client);
        client->timer = -1;
    }
}

void exec_player_command(struct client_entry *client,
    struct server *server, char *line)
{
    char *cmd = NULL;

    for (int i = 0; i < NB_COMMAND_PLAYER; i++) {
        cmd = player_command_list[i].command;
        if (!strncmp(cmd, line, strlen(cmd))) {
            time_command(client, server, line, player_command_list[i]);
            return;
        }
    }
    add_to_buffer(&client->buf_to_send, KO, strlen(KO));
    clean_player_command(client);
}
