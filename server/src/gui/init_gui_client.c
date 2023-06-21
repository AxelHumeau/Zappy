/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** init_gui_client
*/

#include "gui/commands.h"
#include "gui/events.h"

int init_gui_client(struct server *server, struct client_entry *client)
{
    struct client_entry *entry = NULL;

    client->is_gui = true;
    send_map_size((char *[]) {}, server, client);
    send_time_request((char *[]) {}, server, client);
    send_map_content((char *[]) {}, server, client);
    send_team_names((char *[]) {}, server, client);
    SLIST_FOREACH(entry, &server->clients, next) {
        if (entry->is_gui)
            continue;
        send_new_player_str(client, entry->id, &entry->player_info);
    }
    return EXIT_SUCCESS;
}
