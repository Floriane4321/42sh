/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** tests_dollar_var
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>

Test(dollar_var_utils, d_boundaries)
{
    char *str1 = "Let me write a env variable: $HOME";

    cr_assert_eq(get_d_start(str1, 0), 29);
    cr_assert_eq(get_d_end(str1 + 29), 5);
}

Test(dollar_var_utils, get_var_value)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool=", NULL};
    env_t *env = load_env(env_b);

    config.set = malloc(sizeof(set_t));
    config.set->name = "foo";
    config.set->var = "bar";
    config.set->next = NULL;
    cr_assert_str_eq(get_var_value("PWD", &config, env), "/");
    cr_assert_str_eq(get_var_value("?", &config, env), "0");
    cr_assert_str_eq(get_var_value("foo", &config, env), "bar");
}

Test(_dollar_var, _get_dollar_vars)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool=", NULL};
    env_t *env = load_env(env_b);
    char *str = strdup("echo $? $PATH $foo");
    int undef = 0;

    config.set = malloc(sizeof(set_t));
    config.set->name = "foo";
    config.set->var = "bar";
    config.set->next = NULL;
    str = get_dollar_vars(str, &undef, &config, env);
    cr_assert_str_eq(str, "echo 0 /bin/ bar");
}

Test(_dollar_var, _undefined_variable, .init=cr_redirect_stderr)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool=", NULL};
    env_t *env = load_env(env_b);
    char *str = strdup("echo $? $banana $foo");
    int undef = 0;

    config.set = malloc(sizeof(set_t));
    config.set->name = "foo";
    config.set->var = "bar";
    config.set->next = NULL;
    str = get_dollar_vars(str, &undef, &config, env);
    cr_assert_stderr_eq_str("banana: Undefined variable.\n");
}