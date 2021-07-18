/*
** EPITECH PROJECT, 2021
** under_shell.c
** File description:
** under shell for parentheses
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../include/minishell.h"
#include "../include/my.h"

void print_list(list_t *list)
{
    for (list_t *tmp = list; tmp != NULL; tmp = tmp->next)
        my_printf("%s\n", tmp->data);
}

int count_rows(char **str)
{
    int len = 0;

    while (str[len] != 0)
        len++;
    return (len);
}

env_t *copy_env(env_t *env)
{
    env_t *cpy = malloc(sizeof(struct env));
    int len = count_rows(env->env_var);

    cpy->env_var = malloc(sizeof(char *) * (len + 1));
    cpy->env_var[len] = 0;
    for (int i = 0; env->env_var[i] != 0; i++)
        cpy->env_var[i] = my_strdup(env->env_var[i]);
    cpy->allocated_var = env->allocated_var;
    cpy->nb_var = env->nb_var;
    cpy->index_path = env->index_path;
    cpy->list_path = create_path_list(cpy);
    return (cpy);
}

int under_shell(env_t *env, char *line, conf_t *config)
{
    pid_t pid = fork();
    int status = 0;
    char *line_dup;

    if (pid == 0) {
        line_dup = strdup(line);
        skip_line(&line_dup, config);
        process_line(line_dup, my_strlen(line), env, config);
        _exit(config->last_status);
    }
    waitpid(pid, &status, 0);
    config->last_status = status;
    return status;
}

int preparation_under_shell(env_t *env, char *line, conf_t *conf)
{
    env_t *cpy = copy_env(env);

    line = replace_point_in_parentheses(line, '@', ';');
    line = &line[1];
    line[my_strlen(line) - 1] = 0;
    return under_shell(cpy, line, conf);
}
