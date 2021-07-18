/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** test the and (&&) and OR (||) op
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(op_and_or, or)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    process_line("cd ./tests/globbing_tests_dir/", 31, env, &config);
    cr_redirect_stdout();
    process_line("ls ABC.txt || ls Component.jsx", 31, env, &config);
    process_line("sdfgsdfg || ls Component.jsx", 29, env, &config);
    cr_assert_stdout_eq_str("ABC.txt\nComponent.jsx\n");
}

Test(op_and_or, and)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    process_line("cd ./tests/globbing_tests_dir/", 31, env, &config);
    cr_redirect_stdout();
    process_line("ls ABC.txt && ls Component.jsx", 31, env, &config);
    process_line("sdfgsdfg && ls Component.jsx", 29, env, &config);
    process_line("ls ABC.txt && sfsdfgsdfgsdfg", 29, env, &config);
    cr_assert_stdout_eq_str("ABC.txt\nComponent.jsx\nABC.txt\n");
}
