/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** entry point for the minishell1
*/

#include <stdlib.h>
#include "../include/minishell.h"
#include "../include/my.h"

int main(int ac, char *av[], char *env[])
{
    env_t *env_local = load_env(env);

    (void)ac;
    (void)av;
    setup_signal_handling();
    prompt(env_local);
    clean_env(env_local);
    return (0);
}
