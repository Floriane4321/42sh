/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** to use linked list easely
*/

#include <stdlib.h>
#include "../include/my.h"
#include "../include/minishell.h"

list_t *add_data_list(list_t **begin, char *data)
{
    list_t *nw_el;

    nw_el = malloc(sizeof(list_t));
    if (nw_el == NULL)
        return (NULL);
    nw_el->data = data;
    nw_el->next = *begin;
    *begin = nw_el;
    return (*begin);
}

void clean_list(list_t *list)
{
    list_t *tmp = list;

    if (tmp == NULL)
        return;
    while (tmp) {
        list = list->next;
        free(tmp->data);
        free(tmp);
        tmp = list;
    }
}

void reverse_list(list_t **begin)
{
    list_t *before = NULL;
    list_t *current = *begin;
    list_t *after;

    while (current != NULL) {
        after = current->next;
        current->next = before;
        before = current;
        current = after;
    }
    *begin = before;
}

int get_list_size(list_t *list)
{
    int i = 0;

    for (list_t *j = list; j; j = j->next)
        i++;
    return (i);
}

void clean_args_tab(char **args_tab)
{
    for (int i = 0; args_tab[i]; i++)
        free(args_tab[i]);
    free(args_tab);
}
