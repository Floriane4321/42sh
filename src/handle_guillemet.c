/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle the guillemet
*/

#include <string.h>
#include <stdlib.h>

#include "../include/minishell.h"

char *clean_gil(char *str)
{
    char *res = calloc(strlen(str), sizeof(char));
    int j = 0;
    char last_char = ' ';

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\"' && last_char != '\\')
            continue;
        res[j++] = str[i];
        last_char = str[i];
    }
    remove_inhibitors(res);
    return (res);
}

int remove_guillemet(list_t *list)
{
    char *tmp;

    for (list_t *li = list; li; li = li->next) {
        if (G_STR(li)[0] == '\"' || G_STR(li)[strlen(G_STR(li)) - 1] == '\"') {
            tmp = G_STR(li);
            li->data = clean_gil(tmp);
        }
    }
    return (0);
}
