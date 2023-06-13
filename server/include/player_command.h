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
    void (*function) (char **, struct client_entry *, struct server *);
} command_t;

void forward(char **, struct client_entry *, struct server *);
void right(char **, struct client_entry *, struct server *);
void left(char **, struct client_entry *, struct server *);
void look(char **, struct client_entry *, struct server *);
void inventory(char **, struct client_entry *, struct server *);
void broadcast(char **, struct client_entry *, struct server *);
void connect_nbr(char **, struct client_entry *, struct server *);
void fork_cmd(char **, struct client_entry *, struct server *);
void eject(char **, struct client_entry *, struct server *);
void take(char **, struct client_entry *, struct server *);
void set(char **, struct client_entry *, struct server *);
void incantation(char **, struct client_entry *, struct server *);

static command_t player_command_list[MAX_COMMAND_PLAYER] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Fork", fork_cmd},
    {"Eject", eject},
    {"Take", take},
    {"Set", set},
    {"Incantation", incantation},
};

#endif /* !PLAYER_COMMAND_H_ */
