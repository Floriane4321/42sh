/*
** EPITECH PROJECT, 2021
** parcing_set.c
** File description:
** fonction of parcing of set
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

int check_equal(char **str_ini)
{
    int i = 0;
    char *str = *str_ini;

    if (str == NULL || my_strlen(str) < 2)
        return (0);
    for (i = 0; str[i] != 0 && str[i] != '='; i++);
    if (str[i] == 0)
        return (0);
    if (str[i] == '=' && str[i + 1] != 0)
        return (1);
    str[i] = '\0';
    *str_ini = str;
    return (0);
}

char *recup_name_set(char *str)
{
    int i = 0;

    for (i = 0; str[i] != 0 && str[i] != '='; i++);
    str[i] = 0;
    return (str);
}

char *recup_var_set(char *str)
{
    int i = 0;

    for (i = 0; str[i] != 0 && str[i] != '='; i++);
    str = &str[i + 1];
    return (str);
}

list_t *replace_arg_in_list(list_t *tmp, char **arg, int i)
{
    tmp->data = recup_name_set(arg[i]);
    tmp->next = malloc(sizeof(struct list));
    tmp->next->data = "=";
    tmp->next->next = malloc(sizeof(struct list));
    tmp->next->next->data = recup_var_set(arg[i]);
    tmp = tmp->next->next;
    return (tmp);
}

char **parcing_set(char **arg)
{
    char **str = NULL;
    list_t *list = malloc(sizeof(struct list));
    list_t *tmp = list;

    for (int i = 0; arg[i] != NULL; i++) {
        if (check_equal(&arg[i]) == 1) {
            tmp = replace_arg_in_list(tmp, arg, i);
        } else
            tmp->data = arg[i];
        tmp->next = malloc(sizeof(struct list));
        tmp = tmp->next;
    }
    tmp->next = NULL;
    for (tmp = list; tmp && tmp->next && tmp->next->next; tmp = tmp->next);
    tmp->next = NULL;
    str = list_to_tab(list);
    return (str);
}
