/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** some utilities for handling string
*/

#include <stdlib.h>

#include "../include/my.h"
#include "../include/minishell.h"

int str_contain(char *str, char c)
{
    if (!str[0])
        return (-1);
    if (str[0] == c)
        return (0);
    for (int i = 1; str[i]; i++) {
        if (str[i] == c && str[i - 1] != '\\')
            return (i);
    }
    return (-1);
}

int char_is(char c, char *str, parser_t *conf)
{
    char la = conf->last_char;

    conf->last_char = c;
    for (int i = 0; str[i]; i++) {
        if (c == '\"' && la != '\\')
            conf->in_gil = !conf->in_gil;
        if (c == str[i] && (!conf->check_in || !conf->in_gil))
            return (1);
    }
    return (0);
}

char *my_strndup(char const *src, int size)
{
    char *dest = malloc(sizeof(char) * (size + 1));

    for (int i = 0; src[i] && i < size; i++)
        dest[i] = src[i];
    dest[size] = '\0';
    return (dest);
}

int compte_char(char *str, char match)
{
    int res = (*str == match) ? 1 : 0;
    int in_gil = 0;
    char last_char = ' ';

    for (int i = 1; str[i]; i++) {
        if (str[i] == '\"' && last_char != '\\')
            in_gil = !in_gil;
        if (str[i] == match && last_char != '\\' && !in_gil)
            res++;
        last_char = str[i];
    }
    return (res);
}

void clean_whitespaces(char *str)
{
    int i = 0;

    while (str[i]) {
        if ((str[i] == ' ' || str[i] == '\t') &&
        (str[i + 1] == ' ' || str[i + 1] == '\t'))
            shift_str_left(str, i);
        i++;
    }
}
