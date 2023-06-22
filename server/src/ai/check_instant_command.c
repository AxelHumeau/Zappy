/*
** EPITECH PROJECT, 2023
** check_instant_command.c
** File description:
** check_instant_command
*/

#include <string.h>
#include "macro.h"
#include "gui/events.h"

void check_fork(struct client_entry *client, struct server *server,
    char *line)
{
    if (!strncmp(line, FORK, strlen(FORK)) && !client->laying_egg) {
        if ((line + strlen(FORK))[0] == '\0') {
            client->egg = malloc(sizeof(struct egg));
            client->egg->id = server->id_egg++;
            client->egg->x = client->player_info->x;
            client->egg->y = client->player_info->y;
            client->egg->team = client->player_info->team;
            client->player_info->team->nb_slots_left++;
            add_to_buffer(&client->buf_to_send, OK, strlen(OK));
            broadcast_to_guis(server, &notify_egg_laying, client->id);
        } else
            add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        client->laying_egg = true;
    }
}

void check_incantation(struct client_entry *client, struct server *server,
    char *line)
{
    struct client_entry **list_players = NULL;
    int *list_ids = NULL;
    int size = 0;

    if (!strncmp(line, INCANTATION, strlen(INCANTATION)) && !client->ritual) {
        list_players = condition_ritual(client, server);
        if ((line + strlen(INCANTATION))[0] == '\0' && list_players != NULL) {
            size = list_ids_size(list_players);
            list_ids = get_list_ids(list_players, size);
            broadcast_to_guis(server, &notify_start_of_incantation,
                client->id, client->player_info, size, list_ids);
            send_ritual_message(client, list_players, true);
        } else
            add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        client->ritual = true;
    }
    free(list_players);
}
