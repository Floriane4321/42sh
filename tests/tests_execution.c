/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** test with simple commande
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(simple_exec, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    cr_assert_eq(process_line("", 0, env, &config), 1);
    process_line("cd /dev", 9, env, &config);
    cr_redirect_stdout();
    process_line("ls tty", 8, env, &config);
    cr_assert_stdout_eq_str("tty\n");
}

Test(simple_exec, not_found)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    cr_redirect_stderr();
    process_line("nooo tty1", 10, env, &config);
    cr_assert_stderr_eq_str("nooo: Command not found.\n");
}

Test(simple_exec, execv_errro)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    list_t *list_arg = parse_line("nope", 5, " \t", 0);
    char *command = my_strdup("yoo");

    cr_assert_eq(process_execution(list_arg, command, env, &config), 2);
}
