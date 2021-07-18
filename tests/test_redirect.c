/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** test file for redirection
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(redir, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    char *expect = "Missing name for redirect.\nAmbiguous output redirect.\n";

    process_line("cd /dev", 7, env, &config);
    cr_redirect_stderr();
    process_line("ls tty1 >", 10, env, &config);
    process_line("ls tty1 > tmp | wc", 18, env, &config);
    cr_assert_stderr_eq_str(expect);
}

Test(redir, test2)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    char *line1 = "ls tty > /tmp/test_mini ; cat /tmp/test_mini";
    char *line2 = "ls tty >> /tmp/test_mini ; cat /tmp/test_mini";

    process_line("cd /dev", 7, env, &config);
    cr_redirect_stdout();
    process_line(line1, 44, env, &config);
    process_line(line2, 45, env, &config);
    cr_assert_stdout_eq_str("tty\ntty\ntty\n");
}
