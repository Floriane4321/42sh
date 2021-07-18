/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** all the interaction that the user can have
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "../include/minishell.h"
#include "../include/my.h"

int clean_str(char *str, int *size)
{
    if (*size == 1 && str[0] == '\n')
        return (1);
    if (str[*size - 1] == '\n') {
        str[*size - 1] = '\0';
        *size -= 1;
    }
    return (0);
}

void print_prompt(conf_t *config, int mode, env_t *env)
{
    if (config->is_tty && mode == 1)
        color_prompt(config, env);
}

void exit_prompt(conf_t *config)
{
    config->termined = 1;
    if (has_been_signal(0)) {
        clearerr(stdin);
        my_printf("\n");
        config->termined = 0;
        return;
    }
    if (config->is_tty)
        printf("exit\n");
}

int skip_line(char **line, conf_t *config)
{
    int line_size = my_strlen(*line);

    if (clean_str(*line, &line_size))
        return 1;
    if (!is_balanced(*line, '\"', config) || !is_balanced(*line, '`', config))
        return 1;
    return 0;
}

int prompt(env_t *env)
{
    conf_t config = create_config();
    char *line = NULL;
    size_t size = 0;

    while (!config.termined) {
        get_git(&config, env);
        print_prompt(&config, 1, env);
        if (getline(&line, &size, stdin) <= 0) {
            exit_prompt(&config);
            continue;
        }
        config.cmd = my_strdup(line);
        if (skip_line(&line, &config))
            continue;
        process_line(line, my_strlen(line), env, &config);
        config.set->var = config.cmd;
    }
    free(line);
    free(config.pi_inf);
    return (config.last_status);
}
