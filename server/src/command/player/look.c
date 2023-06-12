/*
** EPITECH PROJECT, 2023
** look.c
** File description:
** look
*/

#include <string.h>
#include <stdio.h>
#include "macro.h"

static char *get_info_player_pos(struct client_entry *client,
    struct server *server)
{
    char *look_info = NULL;
    int pos_y = client->player_info.y;
    int pos_x = client->player_info.x;

    asprintf(&look_info, "[ player");
    for (int i = 0; i < NB_RESOURCES; i++) {
        for (size_t nb = 0; nb < server->maps[pos_y][pos_x].resources[i]; nb++)
            look_info = concat_info_string(look_info, RESSOURCE_STR[i], true);
    }
    look_info = concat_info_string(look_info, NULL, false);
    return look_info;
}

static void get_look_position(struct client_entry *client,
    struct server *server, int *pos_index, int *pos)
{
    int height = server->height;
    int width = server->width;
    enum direction dir = client->player_info.direction;
    int i = pos_index[0];
    int j = pos_index[1];

    if (DIRECTION[dir][0] == 0) {
        pos[0] = (i * DIRECTION[dir][1] + client->player_info.y) % height;
        pos[1] = (j + client->player_info.x) % width;
    } else {
        pos[0] = (j + client->player_info.y) % height;
        pos[1] = (i * DIRECTION[dir][0] + client->player_info.x) % width;
    }
    pos[0] += (pos[0] < 0) ? height : 0;
    pos[1] += (pos[1] < 0) ? width : 0;
}

static char *get_tile_resources(struct client_entry *client,
    struct server *server, int *index, char *look_info)
{
    int pos[2] = {0};
    int pos_y = 0;
    int pos_x = 0;
    int level = client->player_info.level;
    enum direction dir = client->player_info.direction;

    get_look_position(client, server, index, pos);
    pos_y = pos[0];
    pos_x = pos[1];
    for (int i = 0; i < NB_RESOURCES; i++) {
        for (size_t nb = 0; nb < server->maps[pos_y][pos_x].resources[i]; nb++)
            look_info = concat_info_string(look_info, RESSOURCE_STR[i], true);
    }
    if (index[0] == level && index[1] == -(index[0] * POS_LOOK[dir]))
        return look_info;
    look_info = concat_info_string(look_info, NULL, false);
    return look_info;
}

static char *get_ressources_look
    (struct client_entry *client, struct server *server)
{
    int tmp = 0;
    int value = 0;
    int pos[2] = {0};
    char *look_info = get_info_player_pos(client, server);
    enum direction dir = client->player_info.direction;

    for (int i = 1; i <= client->player_info.level; i++) {
        tmp = -(POS_LOOK[dir] * i);
        value = (POS_LOOK[dir] * i < 0) ? 1 : -1;
        for (int j = POS_LOOK[dir] * i; j != tmp + value; j += value) {
            pos[0] = i;
            pos[1] = j;
            look_info = get_tile_resources(client, server, pos, look_info);
        }
    }
    look_info = concat_info_string(look_info, "]\n", true);
    return look_info;
}

void look(char **cmd, struct client_entry *client, struct server * server)
{
    char *look_info = NULL;

    if (cmd[1] == NULL) {
        look_info = get_ressources_look(client, server);
        add_to_buffer(&client->buf_to_send, look_info, strlen(look_info));
        write_buffer(&client->buf_to_send, client->fd);
        free(look_info);
    } else {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        write_buffer(&client->buf_to_send, client->fd);
    }
}
