/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** buffering
*/

#pragma once

#include <stdlib.h>

typedef struct buffer {
    char *buffer;
    size_t buffer_size;
    size_t max_buffer_size;
} buffer_t;

void init_buffer(buffer_t *buffer);
void add_to_buffer(buffer_t *buffer, char *str, size_t len);
int write_buffer(buffer_t *buffer, int fd);
void destroy_buffer(buffer_t *buffer);
char *get_line_in_buffer(buffer_t *buffer);
