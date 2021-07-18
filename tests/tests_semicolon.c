/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** test file to see is the semi-colon is handle
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(semi_colon, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    char *expected = "      1       1       4\n      5       5      53\n";

    process_line("cd /dev", 9, env, &config);
    cr_redirect_stdout();
    process_line("ls tty | wc; ls include/ | cut -f 1 | wc", 8, env, &config);
    cr_assert_stdout_eq_str(expected);
}
