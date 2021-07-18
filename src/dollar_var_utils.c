/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** dollar_var_ctl
*/

#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my.h"

int get_d_end(char *line)
{
    int i = 0;

    while (line[i] && line[i] != ' ' && line[i] != '\t')
        i++;
    return i;
}

int get_d_start(char *line, int i)
{
    while (line[i] && line[i] != '$') {
        if (!skip_q_mark(line, &i))
            i++;
    }
    return i;
}

char *get_local_var(char *name, conf_t *c)
{
    for (set_t *set = c->set; set; set = set->next) {
        if (!strcmp(set->name, name))
            return set->var;
    }
    return NULL;
}

char *get_var_value(char *var_name, conf_t *conf, env_t *env)
{
    char *value = NULL;

    if (!strcmp(var_name, "?")) {
        return my_sprintf("%d", conf->last_status);
    }
    if (strlen(var_name) == 0)
        return strdup("$");
    value = get_local_var(var_name, conf);
    if (value)
        return strdup(value);
    value = get_var(var_name, env);
    if (!value)
        return NULL;
    return strdup(value);
}

void var_err(char *name, conf_t *conf, int *undefined_var)
{
    dprintf(2, "%s: Undefined variable.\n", name + 1);
    conf->last_status = 1;
    *undefined_var = 1;
}