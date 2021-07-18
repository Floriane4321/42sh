/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** stack toolbox
*/

#include <stdlib.h>
#include "../include/minishell.h"
#include "../include/my.h"

void push(list_t **list, char *data)
{
    list_t *nw = malloc(sizeof(list_t));

    nw->next = *list;
    nw->data = my_strdup(data);
    *list = nw;
}

char *pop(list_t **list)
{
    list_t *old = *list;
    char *tmp;

    if (*list == NULL) {
        return my_strdup("");
    }
    tmp = old->data;
    *list = (*list)->next;
    free(old);
    return (tmp);
}
