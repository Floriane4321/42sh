/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** test file for the pipe
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(pipe, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    process_line("cd /dev", 7, env, &config);

    cr_redirect_stdout();
    process_line("ls tty | wc", 13, env, &config);
    cr_assert_stdout_eq_str("      1       1       4\n");
}

Test(pipe, test2)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    cr_redirect_stdout();
    process_line("ls include/ | cut -f 1 | wc", 29, env, &config);
    cr_assert_stdout_eq_str("      5       5      53\n");
}

Test(pipe, test3)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    cr_redirect_stdout();
    process_line("env | wc", 9, env, &config);
    cr_assert_stdout_eq_str("      3       3      26\n");
}
