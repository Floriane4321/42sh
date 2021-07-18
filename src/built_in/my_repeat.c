/*
** EPITECH PROJECT, 2021
** my_repeat.c
** File description:
** repeat buit in
*/

#include "minishell.h"
#include "my.h"
#include <stdlib.h>

int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] > '9' || str[i] < '0')
            return (1);
    return (0);
}

char *my_concat(char **av)
{
    int len = 0;
    char *str = NULL;

    for (int i = 0; av[i] != NULL; i++, len++)
        for (int j = 0; av[i][j] != '\0'; j++)
            len++;

    str = calloc(1 + len, sizeof(char));
    for (int i = 0; av[i] != NULL; i++) {
        str = my_strcat(str, av[i]);
        str = my_strcat(str, " ");
    }
    str[len] = '\0';
    return (str);
}

int my_repeat(char **args, env_t *env, conf_t *config)
{
    int nb;
    char *line;

    if (args[1] == NULL || args[2] == NULL) {
        my_putstr("repeat: Too few arguments.\n");
        return (1);
    }
    if (is_num(args[1]) == 1) {
        my_putstr("repeat: Badly formed number.\n");
        return (1);
    }
    nb = my_getnbr(args[1]);
    line = my_concat(&args[2]);
    for (int i = 0; i < nb; i++)
        process_line(line, my_strlen(line), env, config);
    return (0);
}
