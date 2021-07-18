/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** foreach_array_util
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

void clean_foreach_str(char *str)
{
    int len = strlen(str);

    if (str[0] == '(')
        shift_str_left(str, 0);
    if (str[len - 2] == ')')
        str[len - 2] = '\0';
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
    }
}

char **str_to_2darray(char *str)
{
    char **array2d = malloc(sizeof(char *) * 2);
    int size = 1;
    char *tok;

    tok = strtok(str, " ");
    if (!tok) {
        free(array2d);
        return NULL;
    }
    array2d[0] = strdup(tok);
    array2d[size] = NULL;
    while ((tok = strtok(NULL, " ")) != NULL) {
        array2d[size] = strdup(tok);
        size++;
        array2d = realloc(array2d, sizeof(char *) * (size + 1));
        array2d[size] = NULL;
    }
    return array2d;
}