/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle everithing for the config
*/

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/my.h"
#include "../include/minishell.h"

conf_t create_config(void)
{
    conf_t res = {0};

    if (isatty(0) == 1)
        res.is_tty = 1;
    res.last_dir = NULL;
    res.nb_child = 0;
    res.set = add_node_set("_", NULL, NULL);
    res.is_git = 0;
    res.git_branch = NULL;
    res.pi_inf = malloc(sizeof(pipe_inf_t));
    res.is_git = 0;
    res.git_branch = NULL;
    res.history =  tmpfile();
    res.line_count_hist = 0;
    return (res);
}
