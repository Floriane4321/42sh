/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle redirection to file
*/

#include "../include/minishell.h"
#include "../include/my.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int out_redirect(char *line, env_t *env, conf_t *conf, int index)
{
    char *f_name = line + index + ((line[index + 1] == '>') ? 2 : 1);
    list_t *l = parse_line(f_name, my_strlen(f_name), " \t", 0);

    (void) env;
    if (l == NULL)
        return (print_and_return("Missing name for redirect.\n", 1));
    if (conf->pi_inf->out) {
        clean_list(l);
        return (print_and_return("Ambiguous output redirect.\n", 1));
    }
    conf->pi_inf->pipes[conf->pi_inf->c_p].p[1] = open(l->data,
        ((line[index + 1] == '>') ? O_APPEND : O_TRUNC) | OPEN_FLAG, 420);
    if (conf->pi_inf->pipes[conf->pi_inf->c_p].p[1] < 0) {
        clean_list(l);
        my_errprintf("%s %s.\n", l->data, strerror(errno));
        return (1);
    }
    clean_list(l);
    conf->pi_inf->out = 1;
    return (0);
}

int in_redirect(char *line, env_t *env, conf_t *conf, int index)
{
    char *f_name = line + index + 1;
    list_t *l = parse_line(f_name, my_strlen(f_name), " \t", 0);

    (void) env;
    if (l == NULL || l->data == NULL)
        return (print_and_return("Missing name for redirect.\n", 1));
    if (conf->pi_inf->in) {
        clean_list(l);
        return (print_and_return("Ambiguous input redirect.\n", 1));
    }
    conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[0] = open(l->data, 0);
    if (conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[0] < 0) {
        clean_list(l);
        my_errprintf("%s %s.\n", l->data, strerror(errno));
        return (1);
    }
    clean_list(l);
    conf->pi_inf->in = 1;
    return (0);
}

int in_long_redirect(char *line, env_t *env, conf_t *conf, int index)
{
    char *f_name = line + index + 2;
    list_t *l = parse_line(f_name, my_strlen(f_name), " \t", 0);

    (void)env;
    if (conf->pi_inf->in)
        return (print_and_return("Ambiguous input redirect.\n", 1));
    conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[0] =
        create_tmp_file(G_STR(l));
    if (conf->pi_inf->pipes[conf->pi_inf->c_p - 1].p[0] == -1)
        return (print_and_return("Error on tmp file.\n", 1));
    conf->pi_inf->in = 1;
    clean_list(l);
    return (0);
}

int process_redirection(char *line, env_t *env, conf_t *conf, int *err)
{
    list_t *l = parse_line(line, my_strlen(line), "<>", 0);
    int has_out = str_contain(line, '>');
    int has_in = str_contain(line, '<');

    if (has_out != -1 && out_redirect(line, env, conf, has_out))
        return (*err = -2);
    if (has_in != -1 && line[has_in + 1] != '<' &&
            in_redirect(line, env, conf, has_in))
        return (*err = -2);
    if (has_in != -1 && line[has_in + 1] == '<' &&
            in_long_redirect(line, env, conf, has_in))
        return (*err = -2);
    has_out = process_command(l->data, my_strlen(l->data), env, conf);
    if (has_out == -1)
        *err = -1;
    return (has_out);
}
