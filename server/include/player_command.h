/*
** EPITECH PROJECT, 2023
** player_command.h
** File description:
** player_command
*/

#ifndef PLAYER_COMMAND_H_
    #define PLAYER_COMMAND_H_

    #include "macro.h"

typedef struct command_s {
    char *command;
    void (*function) (char *, struct client_entry *, struct server *);
    int cooldown;
} command_t;

void forward(char *, struct client_entry *, struct server *);
void right(char *, struct client_entry *, struct server *);
void left(char *, struct client_entry *, struct server *);
void look(char *, struct client_entry *, struct server *);
void inventory(char *, struct client_entry *, struct server *);
void broadcast(char *, struct client_entry *, struct server *);
void connect_nbr(char *, struct client_entry *, struct server *);
void fork_cmd(char *, struct client_entry *, struct server *);
void eject(char *, struct client_entry *, struct server *);
void take(char *, struct client_entry *, struct server *);
void set(char *, struct client_entry *, struct server *);
void incantation(char *, struct client_entry *, struct server *);

static command_t player_command_list[NB_COMMAND_PLAYER] = {
    {"Forward", forward, 7},
    {"Right", right, 7},
    {"Left", left, 7},
    {"Look", look, 7},
    {"Inventory", inventory, 1},
    {"Broadcast", broadcast, 7},
    {"Connect_nbr", connect_nbr, 0},
    {"Fork", fork_cmd, 42},
    {"Eject", eject, 7},
    {"Take", take, 7},
    {"Set", set, 7},
    {"Incantation", incantation, 300},
};

#endif /* !PLAYER_COMMAND_H_ */
