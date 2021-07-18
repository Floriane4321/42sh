/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** built_in exec 
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/builtin.h"
#include "../include/my.h"

int is_builtin(char *command)
{
    for (int i = 0; i < nb_built_in; i++) {
        if (my_strcmp(command, builts_in[i].command) == 0)
            return (i);
    }
    return (-1);
}

void save_std(int *in, int *out)
{
    *in = dup(STDIN_FILENO);
    *out = dup(STDOUT_FILENO);
}

void restore_std(int in, int out)
{
    dup2(in, STDIN_FILENO);
    close(in);
    dup2(out, STDOUT_FILENO);
    close(out);
}

int builtin_execution(list_t *list_args, env_t *env, conf_t *config)
{
    int built_in_index = is_builtin(list_args->data);
    char **tab_args;
    int ret, save_in, save_out;

    remove_guillemet(list_args);
    tab_args = list_to_tab(list_args);
    if (config->pi_inf->in || config->pi_inf->out) {
        save_std(&save_in, &save_out);
        exec_pipe(config, 0);
    }
    ret = builts_in[built_in_index].func(tab_args, env, config);
    config->last_status = ret;
    if (config->pi_inf->out) {
        close(config->pi_inf->pipes[config->pi_inf->c_p].p[1]);
    }
    if (config->pi_inf->in || config->pi_inf->out)
        restore_std(save_in, save_out);
    clean_list(list_args);
    free(tab_args);
    return (ret);
}
