/*
** EPITECH PROJECT, 2021
** where.c
** File description:
** built in where
*/

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

int count_word(char *str, char sepa)
{
    int i = 0;
    int comp = 0;
    int tmp = 0;

    while (str[i] != '\0') {
        if (tmp == 0 && str[i] != sepa) {
            comp++;
            tmp = 1;
        } else if (tmp == 1 && str[i] == sepa)
            tmp = 0;
        i++;
    }
    return (comp);
}

char **parc_word(char *str, char sepa)
{
    int len = count_word(str, sepa);
    char **new = malloc(sizeof(char *) * (1 + len));
    int tmp = 0;
    int old = 0;

    new[len] = NULL;
    for (int i = 0; i < len; i++) {
        while (str[tmp] != sepa && str[tmp] != '\0')
            tmp++;
        new[i] = malloc(sizeof(char) * (1 + tmp - old));
        new[i] = my_strncpy(new[i], &str[old], tmp - old);
        new[i][tmp - old] = '\0';
        tmp++;
        old = tmp;
    }
    return (new);
}

int access_all_where(char **path, char *fct)
{
    char *tmp;
    int ret = 1;
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
            ret = 0;
        }
        free(tmp);
    }
    return (ret);
}

int path_split_where(char **var, env_t *env)
{
    char *path = get_var("PATH", env);
    char **pa;

    if (path == NULL)
        return (0);
    pa = parc_word(path, ':');
    return (access_all_where(pa, var[1]));
}

int my_where(char **args, env_t *env, conf_t *config)
{
    (void)config;
    if (args[1] == NULL) {
        my_putstr(args[0]);
        my_putstr(": Too few arguments.\n");
        return (1);
    }
    if (is_builtin(args[1]) != -1) {
        my_putstr(args[1]);
        my_putstr(" is a shell built-in\n");
    }
    if (path_split_where(args, env) == 1)
        return (1);
    return (0);
}
