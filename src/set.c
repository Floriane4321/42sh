/*
** EPITECH PROJECT, 2021
** set.c
** File description:
** fonction of command set
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

void change_value_set(char *arg, set_t *set, set_t *now)
{
    set_t *cell = NULL;

    if (arg[0] == '$') {
        cell = find_current_node(set, &arg[1]);
        if (cell == NULL)
            now->var = NULL;
        else
            now->var = cell->var;
    } else
        now->var = my_strdup(arg);
}

int check_variable(char *var, set_t *new, set_t *set)
{
    if (var == NULL) {
        new->var = NULL;
        return (0);
    }
    if (var[0] == '$' && var[1] != 0) {
        if (IS_NUM(var[1]))
            new->var = NULL;
        else if (IS_AL(var[1]))
            change_value_set(var, set, new);
        else {
            my_errprintf("%s: Undefined variable.\n", &var[1]);
            free(new);
            return (1);
        }
    } else if (var[0] == '$')
        new->var = my_strdup("$");
    else
        new->var = my_strdup(var);
    return (0);
}

set_t *add_node_set(char *name, char *var, set_t *set)
{
    set_t *new = malloc(sizeof(struct set_s));

    new->name = my_strdup(name);
    new->next = NULL;
    new->var = NULL;
    if (var == NULL)
        return (new);
    check_variable(var, new, set);
    return (new);
}

set_t *execution_set(set_t *now, set_t *list, char **args, int nb)
{
    if (now == NULL) {
        if (nb == 1 && count_rows(args) > 2)
            now = add_node_set(args[0], args[2], list);
        if (nb == 2 || count_rows(args) == 2)
            now = add_node_set(args[0], NULL, list);
        list = add_end(list, now);
    } else {
        if (nb == 1 && count_rows(args) > 2)
            check_variable(args[2], now, list);
        if (nb == 2)
            now->var = NULL;
    }
    return (list);
}

void disp_env_set(set_t *set)
{
    for (set_t *tmp = set; tmp; tmp = tmp->next) {
        my_putstr(tmp->name);
        my_putstr("\t");
        if (tmp->var != NULL)
            my_putstr(tmp->var);
        my_putstr("\n");
    }
}
