/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle the alias
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "../include/minishell.h"
#include "../include/my.h"

alias_t *is_alias(char *cmd, conf_t *config)
{
    alias_t *alias = NULL;
    int i;
    char back;

    for (i = 0; cmd[i] && cmd[i] != ' ' && cmd[i] != '\t'; i++);
    back = cmd[i];
    cmd[i] = '\0';
    for (list_t *li = config->list_alias; li; li = li->next) {
        if (my_strcmp(cmd, G_ALIAS(li)->cmd_name) == 0) {
            alias = G_ALIAS(li);
            break;
        }
    }
    cmd[i] = back;
    return (alias);
}

int process_alias(char *line, conf_t *conf, env_t *env)
{
    list_t *list_part = parse_line(line, strlen(line), " \t;", 0);
    alias_t *al = (list_part) ? is_alias(G_STR(list_part), conf) : NULL;
    char *new_line;
    int i = 0;
    parser_t confpars = {0, 1, ' '};

    if (al == NULL) {
        clean_list(list_part);
        return (0);
    }
    new_line = calloc(strlen(line) + strlen(al->rem) + 3, sizeof(char));
    for (i = 0; line[i] && char_is(line[i], " \t", &confpars); i++);
    for (i = 0; line[i] && !char_is(line[i], " \t", &confpars); i++);
    strcpy(new_line, al->rem);
    strcpy(new_line + strlen(al->rem), line + i);
    process_line(new_line, strlen(new_line), env, conf);
    return (1);
}

int print_alias(conf_t *conf, char **args)
{
    if (args[1] != NULL && args[2] == NULL)
        return (print_and_return("alias: please provide arguments\n", 1));
    for (list_t *li = conf->list_alias; li; li = li->next) {
        dprintf(1, "%s\t%s\n", G_ALIAS(li)->cmd_name, G_ALIAS(li)->rem);
    }
    return (0);
}
