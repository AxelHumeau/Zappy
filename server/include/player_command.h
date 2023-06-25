/*
** EPITECH PROJECT, 2023
** player_command.h
** File description:
** player_command
*/

#ifndef PLAYER_COMMAND_H_
    #define PLAYER_COMMAND_H_

    #include "macro.h"

/// @brief command_t structure
/// @brief function server/ai
/// @param string the argument of the command
/// @param client_entry pointer of the client
/// @param server pointer to the server
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

/// @brief PLAYER_COMMAND_LIST array
static command_t PLAYER_COMMAND_LIST[NB_COMMAND_PLAYER] = {
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
