/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** the echo builtin
*/

#include <stdlib.h>
#include <string.h>

#include "../include/minishell.h"
#include "../include/my.h"

int my_echo(char **args, env_t *env, conf_t *config)
{
    int put_end_line = 1;

    (void)env;
    (void)config;
    for (int i = 1; args[i]; i++) {
        if (strcmp(args[i], "-n") == 0) {
            put_end_line = 0;
            continue;
        }
        my_printf("%s", args[i]);
        if (args[i + 1])
            my_putstr(" ");
    }
    if (put_end_line)
        my_putstr("\n");
    return (0);
}
