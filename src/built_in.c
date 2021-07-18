/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** where the built in foncion is
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

int my_cd(char **args, env_t *env, conf_t *config)
{
    char *nw_dir = args[1];

    if (nw_dir == NULL || nw_dir[0] == '\0')
        nw_dir = get_var("HOME", env);
    else if (my_strcmp(args[1], "-") == 0)
        nw_dir = pop(&config->last_dir);
    if (args[1] && my_strcmp(args[1], "~") == 0)
        nw_dir = get_var("HOME", env);
    if (nw_dir == NULL)
        nw_dir = "/home/";
    errno = 0;
    if (chdir(nw_dir) < 0) {
        my_errprintf("%s: %s.\n", nw_dir, strerror(errno));
        return (1);
    }
    if (args[1] && my_strcmp(args[1], "-") != 0)
        push(&config->last_dir, my_strdup(get_pwd(env)));
    update_pwd(env);
    return (0);
}

int my_exit(char **args, env_t *env, conf_t *config)
{
    (void)args;
    (void)env;
    config->termined = 1;
    return (config->last_status);
}

int my_env(char **args, env_t *env, conf_t *config)
{
    (void)args;
    (void)config;
    for (int i = 0; i < env->nb_var; i++) {
        my_printf("%s\n", env->env_var[i]);
    }
    return (0);
}

int my_setenv(char **args, env_t *env, conf_t *config)
{
    int arg1_size, arg2_size, index;
    char *res;

    if (args[1] == NULL)
        return (my_env(args, env, config));
    if (env->nb_var + 2 > env->allocated_var)
        realloc_env(env);
    index = get_var_index(args[1], env);
    if (setenv_err(args))
        return (1);
    arg1_size = my_strlen(args[1]);
    arg2_size = (args[2] != NULL) ? my_strlen(args[2]) : 0;
    res = my_calloc(arg1_size + arg2_size + 3, sizeof(char));
    my_memcpy(res, args[1], arg1_size);
    res[arg1_size] = '=';
    my_memcpy(res + arg1_size + 1, args[2], arg2_size);
    if (index != -1)
        free(env->env_var[index]);
    env->env_var[(index == -1) ? env->nb_var++ : index] = res;
    return (update_path(args[1], env));
}

int my_unsetenv(char **args, env_t *env, conf_t *config)
{
    int index;

    (void)config;
    if (args[1] == NULL)
        return (print_and_return("unsetenv: Too few arguments.\n", 2));
    for (int j = 1; args[j] != NULL; j++) {
        index = get_var_index(args[j], env);
        if (index == -1)
            continue;
        free(env->env_var[index]);
        env->nb_var -= 1;
        for (int i = index; i < env->nb_var; i++)
            env->env_var[i] = env->env_var[i + 1];
        env->env_var[env->nb_var] = NULL;
    }
    env->index_path = get_var_index("PATH", env);
    return (0);
}
