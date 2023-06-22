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
    struct position pos = {client->player_info->x, client->player_info->y};

    asprintf(&look_info, "[ player");
    look_info = add_tiles_elem_string(server, client, pos, look_info);
    look_info = concat_info_string(look_info, NULL, false);
    return look_info;
}

static void get_look_position(struct client_entry *client,
    struct server *server, struct position index, struct position *pos)
{
    int height = server->height;
    int width = server->width;
    enum direction dir = client->player_info->direction;
    int i = index.y;
    int j = index.x;

    if (DIRECTION[dir][0] == 0) {
        pos->y = (i * DIRECTION[dir][1] + client->player_info->y) % height;
        pos->x = (j + client->player_info->x) % width;
    } else {
        pos->y = (j + client->player_info->y) % height;
        pos->x = (i * DIRECTION[dir][0] + client->player_info->x) % width;
    }
    pos->y += (pos->y < 0) ? height : 0;
    pos->x += (pos->x < 0) ? width : 0;
}

static char *get_tile_resources(struct client_entry *client,
    struct server *server, struct position index, char *look_info)
{
    struct position pos = {0, 0};
    int level = client->player_info->level;
    enum direction dir = client->player_info->direction;

    get_look_position(client, server, index, &pos);
    look_info = add_tiles_elem_string(server, client, pos, look_info);
    if (index.y == level && index.x == -(index.y * POS_LOOK[dir]))
        return look_info;
    look_info = concat_info_string(look_info, NULL, false);
    return look_info;
}

static char *get_ressources_look
    (struct client_entry *client, struct server *server)
{
    int tmp = 0;
    int value = 0;
    struct position index = {0, 0};
    char *look_info = get_info_player_pos(client, server);
    enum direction dir = client->player_info->direction;

    for (int i = 1; i <= client->player_info->level; i++) {
        tmp = -(POS_LOOK[dir] * i);
        value = (POS_LOOK[dir] * i < 0) ? 1 : -1;
        for (int j = POS_LOOK[dir] * i; j != tmp + value; j += value) {
            index.y = i;
            index.x = j;
            look_info = get_tile_resources(client, server, index, look_info);
        }
    }
    look_info = concat_info_string(look_info, "]\n", true);
    return look_info;
}

void look(char *cmd, struct client_entry *client, struct server * server)
{
    char *look_info = NULL;

    if (cmd[0] == '\0') {
        look_info = get_ressources_look(client, server);
        add_to_buffer(&client->buf_to_send, look_info, strlen(look_info));
        free(look_info);
    } else
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
}
