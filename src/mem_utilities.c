/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** some utilities for the memorie management
*/

#include <stdlib.h>

#include "../include/minishell.h"
#include "../include/my.h"

void realloc_env(env_t *env)
{
    char **new_place = malloc(sizeof(char *) * env->allocated_var * 2);

    env->allocated_var *= 2;
    for (int i = 0; i < env->nb_var; i++) {
        new_place[i] = env->env_var[i];
    }
    free(env->env_var);
    env->env_var = new_place;
}
