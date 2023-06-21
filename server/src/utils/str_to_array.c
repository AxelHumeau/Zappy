/*
** EPITECH PROJECT, 2022
** str_to_array.c
** File description:
** str_to_array
*/

#include <stdlib.h>
#include <stddef.h>

static int check_char(char *separator, char c)
{
    for (int i = 0; separator[i] != '\0'; i++) {
        if (separator[i] == c)
            return 1;
    }
    return 0;
}

static void create_array(char **array, char *str, char *separator)
{
    int x = 0;
    int y = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (check_char(separator, str[i]) == 0 &&
        (check_char(separator, str[i + 1]) == 0 || str[i + 1] != '\0')) {
            array[x][y] = str[i];
            y++;
        }
        if (check_char(separator, str[i]) == 0 &&
        (check_char(separator, str[i + 1]) == 1 || str[i + 1] == '\0')) {
            array[x][y] = '\0';
            x++;
            y = 0;
        }
    }
    array[x] = NULL;
}

static int count_str(char *str, char *separator)
{
    int count = 0;
    int i = 0;
    int cond1 = 0;
    int cond2 = 0;
    int cond3 = 0;

    for (; str[i] != '\0'; i++) {
        cond1 = check_char(separator, str[i]) == 0;
        cond2 = check_char(separator, str[i + 1]) == 1;
        cond3 = str[i + 1] == '\0';
        if (cond1 && (cond2 || cond3))
            count++;
    }
    return count;
}

char **str_to_array(char *str, char *separator)
{
    int count = count_str(str, separator);
    int size = 0;
    int j = 0;
    char **array = malloc(sizeof(char *) * (count + 1));

    for (int i = 0; str[i] != '\0'; i++) {
        if (check_char(separator, str[i]) == 0 &&
        (check_char(separator, str[i + 1]) == 0 || str[i + 1] != '\0'))
            size++;
        if (check_char(separator, str[i]) == 0 &&
        (check_char(separator, str[i + 1]) == 1 || str[i + 1] == '\0')) {
            array[j] = malloc(sizeof(char) * (size + 1));
            j++;
            size = 0;
        }
    }
    create_array(array, str, separator);
    return array;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
