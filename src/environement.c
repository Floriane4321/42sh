/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle everithing related to the environement variable
*/

#include <stdlib.h>
#include "../include/minishell.h"
#include "../include/my.h"

int check_empty_env(env_t *env)
{
    int index = get_var_index("PWD", env);

    if (index != -1)
        return (0);
    env->env_var[env->nb_var++] = my_strdup("PWD=");
    update_pwd(env);
    return (1);
}

env_t *load_env(char *env[])
{
    env_t *res = malloc(sizeof(env_t));

    if (res == NULL)
        return (NULL);
    for (res->nb_var = 0; env[res->nb_var]; res->nb_var++);
    res->allocated_var = (res->nb_var + 1) * 2;
    res->env_var = my_calloc(res->allocated_var, sizeof(char *));
    if (res->env_var == NULL) {
        free(res);
        return (NULL);
    }
    res->index_path = -1;
    for (int i = 0; i < res->nb_var; i++) {
        res->env_var[i] = my_strdup(env[i]);
        if (my_strncmp(res->env_var[i], "PATH=", 5) == 0)
            res->index_path = i;
    }
    res->list_path = create_path_list(res);
    check_empty_env(res);
    return (res);
}

char *get_path_dir(char *str, int *size)
{
    int i;
    char *res;

    for (i = 0; str[i] && str[i] != ':'; i++);
    res = malloc(sizeof(char) * (i + 1));
    for (int j = 0; j < i; j++)
        res[j] = str[j];
    res[i] = '\0';
    *size = i;
    return (res);
}

list_t *create_path_list(env_t *env)
{
    list_t *res = NULL;
    char *paths;
    int size_path;
    char *tmp;
    int i, tmp_size;

    if (env->index_path < 0)
        return (NULL);
    paths = env->env_var[env->index_path];
    size_path = my_strlen(paths);
    for (i = 0; paths[i] && paths[i] != '='; i++);
    i++;
    while (i < size_path) {
        tmp = get_path_dir(paths + i, &tmp_size);
        add_data_list(&res, tmp);
        i += tmp_size + 1;
    }
    reverse_list(&res);
    return (res);
}

int get_var_index(char *var, env_t *env)
{
    int index = -1;
    int size_match;

    if (var == NULL)
        return (index);
    size_match = my_strlen(var);
    for (int i = 0; i < env->nb_var; i++)
        if (my_strncmp(env->env_var[i], var, size_match) == 0 &&
                env->env_var[i][size_match] == '=')
            index = i;
    return (index);
}
