/*
** EPITECH PROJECT, 2021
** my_foreach.c
** File description:
** buit in foreach
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"

int check_variable(char *var, set_t *new, set_t *set);

char **next_cmd_add(char *str, char **new, int nb)
{
        new = realloc(new, sizeof(char *) * nb);
        new[nb - 2] = my_strdup(str);
        new[nb - 1] = NULL;
        return (new);
}

char **get_line_foreach(void)
{
    char *str = NULL;
    size_t size = 0;
    int nb = 1;
    char **new = malloc(sizeof(char *) * nb);

    new[0] = NULL;
    while (1) {
        my_putstr("foreach ? ");
        if (getline(&str, &size, stdin) <= 0) {
            my_putstr("foreach: end not found.\n");
            return (NULL);
        }
        str[my_strlen(str) - 1] = '\0';
        if (my_strcmp(str, "end") == 0)
            return (new);
        nb++;
        new = next_cmd_add(str, new, nb);
    }
    return (NULL);
}

int exec_foreach(char **word, env_t *env, conf_t *config, char *var)
{
    char **cmd = get_line_foreach();

    if (cmd == NULL)
        return (1);
    for (int i = 0; word[i] != NULL; i++) {
        check_variable(word[i], find_current_node(config->set, var),
        config->set);
        for (int j = 0; cmd[j] != NULL; j++) {
            process_line(cmd[j], my_strlen(cmd[j]), env, config);
        }
    }
    return (0);
}

void clear_args(char **av)
{
    int i = 0;

    for (i = 0; av[i] != NULL; i++)
        clean_foreach_str(av[i]);
    if (my_strcmp(av[i - 1], ")") == 0)
        av[i - 1] = NULL;
    else if (av[i - 1][my_strlen(av[i - 1]) - 1] == ')')
        av[i - 1][my_strlen(av[i - 1]) - 1] = '\0';
}

int my_foreach(char **args, env_t *env, conf_t *config)
{
    if (args[2] == NULL || args[1] == NULL) {
        my_putstr("foreach: Too few arguments.\n");
        return (1);
    }
    if (args[2][0] != '(') {
        if (args[3] == NULL)
            my_putstr("foreach: Too few arguments.\n");
        else
            my_putstr("foreach: Words not parenthesized.\n");
        return (1);
    }
    clear_args(&args[2]);
    config->set = add_end(config->set, add_node_set(args[1], NULL,
    config->set));
    if (exec_foreach(&args[2], env, config, args[1]) == 1)
        return (1);
    return (0);
}
