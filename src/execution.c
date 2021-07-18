/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle the process execution
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

int process_line(char *line, int size, env_t *env, conf_t *config)
{
    list_t *list_part;
    int res = 1;

    add_to_history(line, env, config);
    line = expand_line(line, &size, config);
    list_part = parse_line(line, size, ";", 1);
    for (list_t *l = list_part; l; l = l->next) {
        if (l->data != NULL && l->data[0] == '(') {
            res = preparation_under_shell(env, l->data, config);
            continue;
        }
        if (!(l->data != NULL && l->data[0] == ')')) {
            res = process_command_or(G_STR(l), strlen(G_STR(l)), env, config);
        }
    }
    clean_list(list_part);
    return res;
}

int process_command_and(char *line, int size, env_t *env, conf_t *config)
{
    list_t *list_part = parse_line_match(line, size, "&&", 0);
    int res = 1;

    for (list_t *li = list_part; li; li = li->next) {
        res = process_pipe(G_STR(li), my_strlen(G_STR(li)), env, config);
        if (res != 0)
            break;
    }
    clean_list(list_part);
    return (res);
}

int process_command_or(char *line, int size, env_t *env, conf_t *config)
{
    list_t *list_part = parse_line_match(line, size, "||", 0);
    int res = 1;

    for (list_t *li = list_part; li; li = li->next) {
        res = process_command_and(G_STR(li), my_strlen(G_STR(li)), env, config);
        if (res == 0)
            break;
    }
    clean_list(list_part);
    return (res);
}

int process_command(char *line, int size, env_t *env, conf_t *config)
{
    list_t *list_arg;
    char *command_path;
    int mod_err = 0;

    (void)size;
    line = modify_line(line, config, env, &mod_err);
    size = strlen(line);
    if (mod_err)
        return (1);
    list_arg = parse_line(line, strlen(line), " \t", 1);
    remove_guillemet(list_arg);
    if (list_arg == NULL)
        return (print_and_return("Invalid null command.\n", -1));
    if (is_builtin(list_arg->data) != -1)
        return (builtin_execution(list_arg, env, config));
    command_path = get_commande_path(env, list_arg->data, config);
    if (command_path == NULL)
        return (-1);
    return (process_execution(list_arg, command_path, env, config));
}

int process_execution(list_t *args, char *cmd, env_t *env, conf_t *config)
{
    int ret = 0;
    char **tab;
    pid_t pid = fork();

    if (pid == 0) {
        remove_guillemet(args);
        tab = list_to_tab(args);
        if (config->pi_inf->in || config->pi_inf->out)
            exec_pipe(config, 1);
        ret = execve(cmd, tab, env->env_var);
        my_errprintf("%s: Exec format error. Wrong Architecture..\n", tab[0]);
        exit(2);
    }
    handle_after_exec_pipe(&ret, config, pid);
    clean_list(args);
    free(cmd);
    return (handle_return(ret, config));
}
