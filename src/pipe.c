/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** file for pipe and redirection
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

void set_pipe_conf(int *i, int size_list, conf_t *config)
{
    if (size_list < 1) {
        config->pi_inf->in = 0;
        config->pi_inf->out = 0;
        return;
    }
    config->pi_inf->in = (*i == 0) ? 0 : 1;
    config->pi_inf->out = (*i >= size_list) ? 0 : 1;
    pipe(config->pi_inf->pipes[*i].p);
    config->pi_inf->c_p = *i;
    *i += 1;
}

void clean_pipe_on_error(env_t *env, conf_t *config)
{
    list_t *list_arg = parse_line("error_on_pipe", 15, " \t", 0);

    builtin_execution(list_arg, env, config);
}

int process_pipe(char *line, int size, env_t *env, conf_t *config)
{
    list_t *list_part = parse_line(line, size, "|", 0);
    int size_list = get_list_size(list_part) - 1;
    int res = 1;
    int i = 0;
    int tmp = 0;

    if (compte_char(line, '|') != size_list)
        return (print_and_return("Invalid null command.\n", -1));
    config->pi_inf->pipes = my_calloc((size_list + 2), sizeof(struct pipe_s));
    config->pi_inf->c_p = 1;
    for (list_t *l = list_part; l; l = l->next) {
        set_pipe_conf(&i, size_list, config);
        res = process_redirection((char *)(l->data), env, config, &tmp);
        if (tmp < 0)
            clean_pipe_on_error(env, config);
        if (tmp == -2)
            break;
    }
    return (res);
}

void exec_pipe(conf_t *conf, int del_std)
{
    if (conf->pi_inf->in) {
        if (del_std)
            close(conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[1]);
        close(STDIN_FILENO);
        dup2(conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[0], STDIN_FILENO);
    }
    if (conf->pi_inf->out) {
        if (del_std)
            close(conf->pi_inf->pipes[conf->pi_inf->c_p].p[0]);
        close(STDOUT_FILENO);
        dup2(conf->pi_inf->pipes[conf->pi_inf->c_p].p[1], STDOUT_FILENO);
    }
}

void handle_after_exec_pipe(int *ret, conf_t *config, pid_t pid)
{
    if (config->pi_inf->out == 0) {
        waitpid(pid, ret, 0);
        if (has_been_signal(0)) {
            kill(pid, SIGINT);
        }
        for (; config->nb_child > 0; config->nb_child -= 1)
            wait(ret);
    } else {
        close(config->pi_inf->pipes[config->pi_inf->c_p].p[1]);
        config->nb_child += 1;
    }
}
