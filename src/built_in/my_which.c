/*
** EPITECH PROJECT, 2021
** which.c
** File description:
** buit in which
*/

#include <stdlib.h>
#include <unistd.h>

#include "my.h"
#include "minishell.h"

char **parc_word(char *str, char sepa);

int access_all_which(char **path, char *fct)
{
    char *tmp;
    int len = 0;

    for (int i = 0; path[i] != NULL; i++) {
        len = my_strlen(path[i]) + my_strlen(fct) + 1;
        tmp = malloc(sizeof(char) * (1 + len));
        tmp = my_strcpy(tmp, path[i]);
        tmp[my_strlen(path[i])] = '/';
        tmp[my_strlen(path[i]) + 1] = '\0';
        tmp = my_strcat(tmp, fct);
        if (access(tmp, F_OK) == 0) {
            my_putstr(tmp);
            my_putchar('\n');
            free(tmp);
            return (0);
        }
        free(tmp);
    }
    return (1);
}

int path_split_which(char **var, env_t *env)
{
    char *path = get_var("PATH", env);
    char **pa;

    if (path == NULL)
        return (1);
    pa = parc_word(path, ':');
    return (access_all_which(pa, var[1]));
}

int my_which(char **args, env_t *env, conf_t *config)
{
    (void)config;
    if (args[1] == NULL) {
        my_putstr(args[0]);
        my_putstr(": Too few arguments.\n");
        return (1);
    }
    if (is_builtin(args[1]) != -1) {
        my_putstr(args[1]);
        my_putstr(": shell built-in command.\n");
        return (0);
    }
    if (path_split_which(args, env) == 1)
        return (1);
    return (0);
}
