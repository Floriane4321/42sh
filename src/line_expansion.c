/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** expand the line with the alias and var
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/minishell.h"
#include "../include/my.h"

int remplace_alias(char **line, alias_t *alias, int *index)
{
    char *res = malloc(strlen(*line) + strlen(alias->rem) + 3);

    if (*index > 0) {
        (*line)[*index] = '\0';
        sprintf(res, "%s %s %s", *line, alias->rem,
                *line + strlen(alias->cmd_name));
    } else {
        sprintf(res, "%s %s", alias->rem,
                *line + strlen(alias->cmd_name));
    }
    free(*line);
    *line = res;
    *index += strlen(res);
    return (0);
}

char *expand_line(char *line, int *size, conf_t *config)
{
    char la = ' ';
    alias_t *al = NULL;
    parser_t pars_conf = {0, 0, ' '};
    char *new_line = strdup(line);

    (void)size;
    for (int i = 0; new_line[i]; i++) {
        if ((al = is_alias(new_line + i, config)) != NULL &&
        !char_is(la, ";|<>&", &pars_conf)) {
            remplace_alias(&new_line, al, &i);
        }
        if (i > (int)strlen(new_line))
            break;
        la = (new_line[i] != ' ' && new_line[i] != '\t') ? new_line[i] : la;
    }
    return (new_line);
}

char *modify_line(char *line, conf_t *config, env_t *env, int *mod_err)
{
    int undefined_var = 0;
    int glob_no_match = 0;

    line = process_backsticks(line, config, env);
    line = get_dollar_vars(line, &undefined_var, config, env);
    line = glob_line(line, ALLOC_TRUE, &glob_no_match, config);
    if (glob_no_match || undefined_var)
        *mod_err = 1;
    return line;
}
