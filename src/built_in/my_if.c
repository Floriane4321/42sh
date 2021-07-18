/*
** EPITECH PROJECT, 2021
** my_if.c
** File description:
** built in if
*/

#include "minishell.h"
#include <stdlib.h>
#include "my.h"

int my_if(char **args, env_t *env, conf_t *config)
{
    char *line;

    if (args[1] == NULL) {
        my_putstr("if: Too few arguments.\n");
        return (1);
    }
    if (args[2] == NULL) {
        my_putstr("if: Empty if.\n");
        return (1);
    }
    if (is_num(args[1]) == 1) {
        my_putstr("if: Expression Syntax.\n");
        return (1);
    }
    line = my_concat(&args[2]);
    if (my_getnbr(args[1]) != 0)
        process_line(line, my_strlen(line), env, config);
    return (0);
}
