/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** tests_quote_marks
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "minishell.h"

Test(quote_marks, balancing)
{
    char *str1 = strdup(" hello\"");
    conf_t conf = {0};

    cr_assert_eq(is_balanced(str1, '\"', &conf), 0);
    str1[0] = '\"';
    cr_assert_eq(is_balanced(str1, '\"', &conf), 1);
    str1[1] = '\"';
    cr_assert_eq(is_balanced(str1, '\"', &conf), 0);
    remove_spe_char(str1, '\"');
    free(str1);
}

Test(quote_marks, _remove_spe_char)
{
    char *str1 = strdup("\"hello\"");

    remove_spe_char(str1, '\"');
    cr_assert_str_eq(str1, "hello");
    free(str1);
}

Test(guillement, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    char *line1 = "ls \"ABC.txt\"";
    char *line2 = "ls \"ABC\"\".txt\"";

    process_line("cd ./tests/globbing_tests_dir/", 31, env, &config);

    cr_redirect_stdout();
    process_line(line1, strlen(line1), env, &config);
    process_line(line2, strlen(line2), env, &config);
    cr_assert_stdout_eq_str("ABC.txt\nABC.txt\n");
}
