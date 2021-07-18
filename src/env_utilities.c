/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** utilities for the env
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "../include/minishell.h"
#include "../include/my.h"

char *get_var(char *var, env_t *env)
{
    int index = -1;
    int size_match;

    if (var == NULL)
        return (NULL);
    size_match = my_strlen(var);
    for (int i = 0; i < env->nb_var; i++)
        if (my_strncmp(env->env_var[i], var, size_match) == 0 &&
                env->env_var[i][size_match] == '=')
            index = i;
    if (index == -1)
        return (NULL);
    return (env->env_var[index] + size_match + 1);
}

char *update_pwd(env_t *env)
{
    char *pwd = malloc(sizeof(char) * 4096);

    my_strcpy(pwd, "PWD=");
    if (getcwd(pwd + 4, 4092) == NULL)
        return (NULL);
    for (int i = 0; i < env->nb_var; i++) {
        if (my_strncmp(env->env_var[i], "PWD=", 4) == 0) {
            free(env->env_var[i]);
            env->env_var[i] = pwd;
        }
    }
    return (pwd + 4);
}

int update_path(char *changed_var, env_t *env)
{
    if (!(my_strncmp(changed_var, "PATH", 4) == 0 && changed_var[4] == '\0'))
        return (0);
    clean_list(env->list_path);
    env->list_path = create_path_list(env);
    return (0);
}

int setenv_err(char **args)
{
    char *msg = "setenv: Variable name must contain alphanumeric characters.";

    if (args[2] != NULL && args[3] != NULL)
        return (print_and_return("setenv: Too many arguments.\n", 1));
    for (int i = 0; args[1][i]; i++)
        if (!(IS_AL(args[1][i]) || IS_NUM(args[1][0]))) {
            my_errprintf("%s\n", msg);
            return (1);
        }
    if (!IS_AL(args[1][0])) {
        my_errprintf("setenv: Variable name must begin with a letter.\n");
        return (1);
    }
    return (0);
}
