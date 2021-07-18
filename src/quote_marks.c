/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** quote_marks
*/

#include "minishell.h"
#include <stdio.h>

char is_balanced(char *line, char c, conf_t *conf)
{
    char balance_status = 1;
    int i = 0;

    while (line[i]) {
        if (line[i] == c && !is_inhibited(line, i))
            balance_status = !balance_status;
        i++;
    }
    if (!balance_status) {
        dprintf(2, "Unmatched \'%c\'.\n", c);
        conf->last_status = 1;
    }
    return balance_status;
}

char skip_q_mark(char *line, int *i)
{
    if (line[*i] != '\"' || (line[*i] == '\"' && is_inhibited(line, *i)))
        return 0;
    (*i)++;
    while (line[*i] && (line[*i] != '\"')) {
        (*i)++;
        if (line[*i] == '\"' && is_inhibited(line, *i))
            (*i)++;
    }
    if (line[*i] == '\"')
        (*i)++;
    return 1;
}

void remove_spe_char(char *line, char c)
{
    int i = 0;

    while (line[i]) {
        if (line[i] == c && !is_inhibited(line, i))
            shift_str_left(line, i);
        i++;
    }
}