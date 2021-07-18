/*
** EPITECH PROJECT, 2021
** parentheses.c
** File description:
** parentheses parcing
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/minishell.h"
#include "../include/my.h"

char *replace_point_in_parentheses(char *line, char replace, char c)
{
    int enter = 0;

    for (int i = 0; line[i] != 0; i++) {
        if (line[i] == '(') {
            if (i > 0 && line[i - 1] == '\\' && line[i] == '(')
                enter--;
            enter++;
        }
        if (line[i] == ')') {
            if (i > 0 && line[i - 1] == '\\' && line[i] == '(')
                enter++;
            enter--;
        }
        if (enter > 0 && line[i] == replace)
            line[i] = c;
    }
    return (line);
}

void add_point_with_parentheses(char *rsl, char c)
{
    if (c == '(') {
        rsl[0] = ';';
        rsl[1] = '(';
    }
    if (c == ')') {
        rsl[0] = ')';
        rsl[1] = ';';
    }
}

int error_parentheses(char *line)
{
    int par_r = count_parentheses(line, '(');
    int par_l = count_parentheses(line, ')');

    if (par_r > par_l) {
        my_errprintf("Too many ('s.\n");
        return (1);
    } else if (par_l > par_r) {
        my_errprintf("Too many )'s.\n");
        return (1);
    }
    for (int i = 0; line[i] != 0; i++) {
        if (i > 0 && line[i] == '(' && is_glob_separator(line, i - 1) != 1) {
            my_errprintf("Badly placed ()'s.\n");
            return (1);
        } else if (line[i + 1] != 0 && line[i] == '(' && line[i + 1] == ')') {
            my_errprintf("Invalid null command.\n");
            return (1);
        }
    }
    return (0);
}

char *parcing_parentheses(char *line, int len, conf_t *config)
{
    int nb = compte_char(line, '(');
    char *rsl = NULL;
    int cmp = 0;

    if (error_parentheses(line) == 1) {
        config->last_status = 1;
        return (line);
    }
    rsl = realloc(rsl, (len + 2 * nb + 1));
    rsl[len + 2 * nb] = 0;
    for (int i = 0; line[i] != 0; i++, cmp++) {
        if (i > 0 && line[i - 1] == '\\' && (line[i] == '(' || line[i] == ')'));
        else if (line[i] == '(' || line[i] == ')') {
            add_point_with_parentheses(&rsl[cmp], line[i]);
            cmp++;
        }
        if (line[i] != '(' && line[i] != ')')
            rsl[cmp] = line[i];
    }
    return (replace_point_in_parentheses(rsl, ';', '@'));
}
