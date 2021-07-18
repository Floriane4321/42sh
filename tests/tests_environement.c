/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** unit test for the env gestion
*/

#include <criterion/criterion.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(env, test1)
{
    char *env[] = {"ls", "PATH=/bin/", "cool", NULL};
    env_t *env_local = load_env(env);

    for (int i = 0; i < 3; i++) {
        cr_assert_str_eq(env_local->env_var[i], env[i]);
    }
    cr_assert_eq(env_local->index_path, 1);
}

Test(env_path, test2)
{
    char *test = "/bin/test:/usr/bin/test";
    int size;
    char *res = get_path_dir(test, &size);

    cr_assert_str_eq("/bin/test", res);
    free(res);
    res = get_path_dir(test + size + 1, &size);
    cr_assert_str_eq("/usr/bin/test", res);
}

Test(env_path, test3)
{
    char *src[] = {"ls",  "PATH=/bin/test:/usr/bin/test", "cool", NULL};
    env_t *env = load_env(src);
    list_t *res = create_path_list(env);
    char *match[] = {"/bin/test", "/usr/bin/test"};

    for (int i = 0; i < 2; i++) {
        cr_assert_str_eq(res->data, match[i]);
        res = res->next;
    }
}

Test(env_path, test4)
{
    char *src[] = {"TEST=ls",  "PATH=/bin/test:/usr/bin/test", NULL};
    char *err[] = {"hello", "jk", "jk", "jk"};
    char *err2[] = {"1hello", "1jk", NULL};
    char *err3[] = {"hell$o", "jk*", NULL};
    char *good[] = {"TEST", "yoo", NULL};
    env_t *env = load_env(src);

    cr_assert_str_eq(get_var("TEST", env), "ls");
    cr_assert_eq(get_var(NULL, env), NULL);
    cr_assert_eq(get_var("NOOOOOO", env), NULL);
    cr_assert_eq(setenv_err(err), 1);
    cr_assert_eq(setenv_err(err2), 1);
    cr_assert_eq(setenv_err(err3), 1);
    cr_assert_eq(setenv_err(good), 0);
    env->index_path = -1;
    cr_assert_eq(create_path_list(env), NULL);
    clean_env(env);
}
