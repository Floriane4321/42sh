/*
** EPITECH PROJECT, 2021
** parentheses_utile.c
** File description:
** utile parentheses fonctions
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/minishell.h"
#include "../include/my.h"

int count_parentheses(char *line, char c)
{
    int nb = 0;

    if (c != '(' && c != ')')
        return (0);
    for (int i = 0; line[i] != 0; i++) {
        if (line[i] == c)
            nb++;
        if (i > 0 && line[i - 1] == '\\' && line[i] == c)
            nb--;
    }
    return (nb);
}
