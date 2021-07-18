/*
** EPITECH PROJECT, 2021
** set_utile.c
** File description:
** fonction utile of set
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

char *get_value_set(set_t *set, char *arg)
{
    set_t *cell = find_current_node(set, arg);

    if (cell == NULL) {
        my_errprintf("%s: Undefined variable.\n", arg);
        return (NULL);
    }
    return (cell->var);
}

int count_cmp(char **args, int i)
{
    if (args[i + 2] == NULL)
        return (i + 1);
    else
        return (i + 2);
}

set_t *find_current_node(set_t *set, char *arg)
{
    for (set_t *tmp = set; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->name, arg) == 0)
            return (tmp);
    }
    return (NULL);
}

set_t *add_end(set_t *list, set_t *cell)
{
    set_t *tmp = list;

    cell->next = NULL;
    if (tmp == NULL)
        return (cell);
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = cell;
    return (list);
}
