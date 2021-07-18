/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle the history
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/minishell.h"
#include "../include/my.h"

int add_to_history(char *line, env_t *env, conf_t *conf)
{
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    char *heure = asctime(local_time);

    (void)env;
    if (conf->history == NULL)
        return (0);
    fprintf(conf->history, "%5u\t%.5s\t%s\n", conf->line_count_hist,
            heure + 11, line);
    return (1);
}

int my_history(char **args, env_t *env, conf_t *config)
{
    char *line = NULL;
    size_t size = 0;

    (void)args;
    (void)env;
    if (config->history == NULL)
        return (1);
    fseek(config->history, 0, SEEK_SET);
    while (getline(&line, &size, config->history) > 0) {
        dprintf(1, "%s", line);
    }
    return (0);
}
