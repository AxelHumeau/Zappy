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
    {"Forward", forward, TIMER_CLASSIC},
    {"Right", right, TIMER_CLASSIC},
    {"Left", left, TIMER_CLASSIC},
    {"Look", look, TIMER_CLASSIC},
    {"Inventory", inventory, TIMER_FAST},
    {"Broadcast", broadcast, TIMER_CLASSIC},
    {"Connect_nbr", connect_nbr, NO_TIMER},
    {"Fork", fork_cmd, TIMER_FORK},
    {"Eject", eject, TIMER_CLASSIC},
    {"Take", take, TIMER_CLASSIC},
    {"Set", set, TIMER_CLASSIC},
    {"Incantation", incantation, TIMER_INCANTATION},
};

#endif /* !PLAYER_COMMAND_H_ */
