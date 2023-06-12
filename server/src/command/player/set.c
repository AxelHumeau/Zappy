/*
** EPITECH PROJECT, 2023
** take.c
** File description:
** take
*/

#include <string.h>
#include "macro.h"

static bool set_object(struct client_entry *client, struct server *server,
    char *object)
{
    int index_object = is_object(object);
    int pos_y = client->player_info.y;
    int pos_x = client->player_info.x;

    if (index_object == -1)
        return false;
    if (client->player_info.inventory[index_object] <= 0)
        return false;
    server->maps[pos_y][pos_x].resources[index_object]++;
    client->player_info.inventory[index_object]--;
    return true;
}

void set(char **cmd, struct client_entry *client, struct server *server)
{
    if (cmd[1] != NULL && cmd[2] == NULL &&
            set_object(client, server, cmd[1])) {
        add_to_buffer(&client->buf_to_send, OK, strlen(OK));
        write_buffer(&client->buf_to_send, client->fd);
    } else {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        write_buffer(&client->buf_to_send, client->fd);
    }
}
