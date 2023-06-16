/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** buffer
*/

#include <unistd.h>
#include <string.h>
#include "buffering.h"
#include "macro.h"

void add_to_buffer(buffer_t *buffer, char *str, size_t len)
{
    if (buffer->buffer_size + len > buffer->max_buffer_size) {
        buffer->buffer = realloc(buffer->buffer,
            sizeof(char[buffer->buffer_size + len]));
        buffer->max_buffer_size = buffer->buffer_size + len;
    }
    for (size_t i = 0; i < len; i++)
        buffer->buffer[buffer->buffer_size + i] = str[i];
    buffer->buffer_size += len;
}

int write_buffer(buffer_t *buffer, int fd)
{
    if (write(fd, buffer->buffer, buffer->buffer_size) == -1)
        return EXIT_FAIL;
    buffer->buffer_size = 0;
    return EXIT_SUCCESS;
}

void init_buffer(buffer_t *buffer)
{
    buffer->buffer = malloc(sizeof(char[MAX_SIZE_BUFFER]));
    buffer->buffer_size = 0;
    buffer->max_buffer_size = MAX_SIZE_BUFFER;
}

void destroy_buffer(buffer_t *buffer)
{
    free(buffer->buffer);
}

char *get_line_in_buffer(buffer_t *buffer)
{
    long pos = (long) memchr(buffer->buffer, '\n', buffer->buffer_size) -
        (long) buffer->buffer;
    size_t tmp;
    char *line;

    if (pos < 0)
        return NULL;
    line = malloc(sizeof(char[pos + 1]));
    strncpy(line, buffer->buffer, pos);
    line[pos] = '\0';
    tmp = buffer->buffer_size - pos - 1;
    buffer->buffer_size = 0;
    add_to_buffer(buffer, buffer->buffer + pos + 1, tmp);
    return line;
}
