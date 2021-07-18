/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** glob_spe_chars_utils
*/

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char has_quoted_char(char *str)
{
    int i = 0;

    while (str[i]) {
        if (str[i] == '\"' && !is_inhibited(str, i))
            return i;
        i++;
    }
    return -1;
}

void shift_str_right(char *str, int i)
{
    int j = strlen(str);

    str = realloc(str, j + 1);
    str[j + 1] = '\0';
    while (j > i) {
        str[j] = str[j - 1];
        j--;
    }
}

char *escape_quoted_chars(char *str)
{
    int i = has_quoted_char(str);

    if (i == -1)
        return str;
    i++;
    while (str[i] != '\"') {
        if (is_glob_char(str, i)) {
            shift_str_right(str, i);
            str[i] = '\\';
            i++;
        }
        i++;
    }
    remove_spe_char(str, '\"');
    return str;
}