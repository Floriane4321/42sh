/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** globbings_utils
*/

#include "minishell.h"

int is_glob_char(char *line, int i)
{
    for (int j = 0; GLOB_CHARS[j]; j++) {
        if (line[i] == GLOB_CHARS[j])
            return 1;
    }
    return 0;
}

int str_has_glob_char(char *line)
{
    int has_glob_char = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        for (int j = 0; GLOB_CHARS[j]; j++) {
            has_glob_char += is_glob_char(line, i);
        }
        if (has_glob_char)
            return 1;
    }
    return 0;
}

char is_glob_separator(char *line, int i)
{
    for (int j = 0; GLOB_SEPS[j]; j++) {
        if (line[i] == GLOB_SEPS[j] && !is_inhibited(line, i))
            return 1;
    }
    return 0;
}

int get_glob_start(char *line)
{
    int i = 0;

    while (line[i] && !is_glob_char(line, i)) {
        if (!skip_q_mark(line, &i))
            i++;
    }
    if (line[i] != '\0') {
        while (i >= 0 && !is_glob_separator(line, i))
            i--;
        if (i < 0)
            i++;
        if (is_glob_separator(line, i))
            i++;
    }
    return i;
}

int get_glob_end(char *line)
{
    int glob_end = 0;

    while (line[glob_end] && !is_glob_separator(line, glob_end))
        glob_end++;
    return glob_end;
}
