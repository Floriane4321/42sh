/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** the seconde file for built-in
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"
#include "../include/my.h"

int my_set(char **args_ini, env_t *env, conf_t *config)
{
    set_t *now = NULL;
    char **args = parcing_set(args_ini);
    int len = count_rows(args);

    (void)env;
    if (args[1] == NULL)
        disp_env_set(config->set);
    for (int i = 1; args[i]; i++) {
        now = find_current_node(config->set, args[i]);
        if (!IS_AL(args[i][0])) {
            my_errprintf("set: Variable name must begin with a letter.\n");
            return (1);
        }
        if (len - i - 1 > 0 && my_strcmp(args[i + 1], "=") == 0) {
            config->set = execution_set(now, config->set, &args[i], 1);
            i = count_cmp(args, i);
        } else
            config->set = execution_set(now, config->set, &args[i], 2);
    }
    return (0);
}

int my_alias(char **args, env_t *env, conf_t *config)
{
    int size_rem = 0;
    alias_t *nw_alias = malloc(sizeof(alias_t));
    int index = 0;

    (void)env;
    if (args[1] == NULL || args[2] == NULL) {
        free(nw_alias);
        return (print_alias(config, args));
    }
    for (int i = 1; args[i]; size_rem += (strlen(args[i++]) + 4));
    nw_alias->cmd_name = my_strdup(args[1]);
    nw_alias->rem = malloc(sizeof(char) * (size_rem + 5));
    for (int i = 2; args[i]; i++) {
        my_strncpy(nw_alias->rem + index, args[i], my_strlen(args[i]));
        index += my_strlen(args[i]);
        nw_alias->rem[index++] = ' ';
    }
    nw_alias->rem[index] = '\0';
    add_data_list(&config->list_alias, (char *)nw_alias);
    return (0);
}

int error_pipe(char **args, env_t *env, conf_t *config)
{
    (void)args;
    (void)env;
    return (config->last_status);
}
