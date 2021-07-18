/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** dollar_var
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

char *replace_dollar_vars(char *line, char *value, int d_start, int d_end)
{
    int size = strlen(line) + strlen(value) + 1;
    char *cpy = strdup(line);

    line = realloc(line, size);
    for (int i = d_end; i >= 0; i--) {
        line[d_start + i] = '\0';
    }
    line = strcat(line, value);
    line = strcat(line, cpy + d_start + d_end);
    free(cpy);
    return line;
}

char *get_dollar_vars(char *line, int *undefined_var, conf_t *c, env_t *env)
{
    char *var_name;
    int d_start = 0;
    int d_end;
    char *var_value = NULL;

    while (line && d_start < (int)strlen(line)) {
        if (str_contain(line + d_start, '$') == -1)
            return line;
        d_start = get_d_start(line, d_start);
        d_end = get_d_end(line + d_start);
        var_name = strndup(line + d_start, d_end);
        var_value = get_var_value(var_name + 1, c, env);
        if (var_value == NULL) {
            var_err(var_name, c, undefined_var);
            return line;
        }
        free(var_name);
        line = replace_dollar_vars(line, var_value, d_start, d_end);
        d_start += d_end;
    }
        return line;
}