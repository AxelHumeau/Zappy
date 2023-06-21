/*
** EPITECH PROJECT, 2023
** broadcast.c
** File description:
** broadcast
*/

#include <string.h>
#include <sys/param.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "macro.h"
#include "gui/events.h"

static double get_distance(struct server *server, struct position zone,
    struct position sender)
{
    int width = server->width;
    int height = server->height;
    int dx = MIN(abs(sender.x - zone.x), width - abs(sender.x - zone.x));
    int dy = MIN(abs(sender.y - zone.y), height - abs(sender.y - zone.y));

    return (sqrtf(dx * dx + dy * dy));
}

static int get_closest_zone(struct position zone[], struct position sender,
    enum direction dir, struct server *server)
{
    int save = 0;
    double save_dist = -1;
    double dist = 0;

    for (int i = 0; i < ZONE_SIZE; i++) {
        dist = get_distance(server, zone[i], sender);
        if (save_dist == -1 || (save_dist != -1 && dist < save_dist)) {
            save = i;
            save_dist = dist;
        }
    }
    if ((save + DIRECTION_ZONE[dir]) % ZONE_SIZE == 0)
        return ZONE_SIZE;
    else
        return (save + DIRECTION_ZONE[dir]) % ZONE_SIZE;
}

static void send_message(int index, char **args, struct client_entry *player)
{
    char *message = NULL;

    asprintf(&message, "message %d,", index);
    for (int i = 0; args[i] != NULL; i++)
        message = concat_info_string(message, args[i], true);
    message = concat_info_string(message, "\n", true);
    add_to_buffer(&player->buf_to_send, message, strlen(message));
    free(message);
}

static void find_closest_zone(struct client_entry *client,
    struct client_entry *player, struct server *server, char **args)
{
    struct position zone[ZONE_SIZE];
    struct position sender = {client->player_info.x, client->player_info.y};
    struct position target = {player->player_info.x, player->player_info.y};
    enum direction dir = player->player_info.direction;
    int index = 0;

    for (int i = 0; i < ZONE_SIZE; i++) {
        zone[i].y = (target.y + ZONE_INDEX[i].y) % server->height;
        zone[i].x = (target.x + ZONE_INDEX[i].x) % server->width;
        zone[i].y += (zone[i].y < 0) ? server->height : 0;
        zone[i].x += (zone[i].x < 0) ? server->width : 0;
    }
    index = get_closest_zone(zone, sender, dir, server);
    if (sender.x == target.x && sender.y == target.y)
        index = 0;
    send_message(index, args, player);
}

void broadcast(char *cmd, struct client_entry *client, struct server *server)
{
    struct client_entry *player = NULL;
    char **args = NULL;

    if (cmd[0] != ' ' && cmd[0] != '\t') {
        add_to_buffer(&client->buf_to_send, KO, strlen(KO));
        return;
    }
    args = str_to_array(cmd, "\t ");
    for (int i = 0; i < server->nb_teams; i++) {
        SLIST_FOREACH(player, &server->clients, next) {
            if (is_player(player, client))
                find_closest_zone(client, player, server, args);
        }
    }
    broadcast_to_guis(server, &notify_broadcast,
        client->id, cmd + 1);
    add_to_buffer(&client->buf_to_send, OK, strlen(OK));
    free_array(args);
}
