/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** cleaning
*/

#include <stdlib.h>

#include "../include/minishell.h"
#include "../include/my.h"

void clean_env(env_t *env)
{
    for (int i = 0; i < env->nb_var; i++)
        free(env->env_var[i]);
    free(env->env_var);
    clean_list(env->list_path);
    free(env);
}
