/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** tests the built in
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(builtin_cd, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool", NULL};
    env_t *env = load_env(env_b);

    process_line("cd /bin", 8, env, &config);
    cr_assert_str_eq(get_pwd(env), "/usr/bin");
    process_line("cd /tmp", 8, env, &config);
    cr_assert_str_eq(get_pwd(env), "/tmp");
    process_line("cd -", 8, env, &config);
    cr_assert_str_eq(get_pwd(env), "/usr/bin");
}

Test(builtin_setenv, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool=", NULL};
    env_t *env = load_env(env_b);

    cr_redirect_stdout();
    process_line("setenv", 7, env, &config);
    cr_assert_stdout_eq_str("PWD=/\nPATH=/bin/\ncool=\n");
    process_line("setenv TOTO coucou", 16, env, &config);
    cr_assert_str_eq(env->env_var[env->nb_var - 1], "TOTO=coucou");
    process_line("setenv TOTO heloo", 15, env, &config);
    cr_assert_str_eq(env->env_var[env->nb_var - 1], "TOTO=heloo");
    process_line("setenv TOTOI hel", 14, env, &config);
    cr_assert_str_eq(env->env_var[env->nb_var - 2], "TOTO=heloo");
    cr_assert_str_eq(env->env_var[env->nb_var - 1], "TOTOI=hel");
    process_line("setenv TOTO1 coucou", 16, env, &config);
}

Test(builtin_unsetenv, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "TOTO=loool", "coucou=",
        "cool", NULL};
    env_t *env = load_env(env_b);

    process_line("unsetenv TOTO coucou", 21, env, &config);
    cr_assert_str_eq(env->env_var[env->nb_var - 2], "PATH=/bin/");
    cr_redirect_stderr();
    process_line("unsetenv", 9, env, &config);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}

Test(builtin_env, test1)
{
    conf_t config = create_config();
    char *env_b[] = {"PWD=/", "PATH=/bin/", "cool=", NULL};
    env_t *env = load_env(env_b);

    cr_redirect_stdout();
    process_line("env", 4, env, &config);
    cr_assert_stdout_eq_str("PWD=/\nPATH=/bin/\ncool=\n");
}
