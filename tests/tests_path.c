/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** description
*/

#include <criterion/criterion.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(path, test1)
{
    cr_assert(command_in_folder("echo", "/bin"));
    cr_assert(!command_in_folder("existe_pas", "/bin"));
}

Test(path, test2)
{
    char *src[] = {"ls",  "PATH=/usr/bin:/usr/bin/test", "cool", NULL};
    env_t *env = load_env(src);
    conf_t conf = create_config();

    cr_assert_str_eq(get_commande_path(env, "diff", &conf), "/usr/bin/diff");
}

Test(path, test3_err)
{
    char *src[] = {"ls",  "PATH=/usr/bin/nooop:/usr/bin/test", "cool", NULL};
    env_t *env = load_env(src);
    conf_t conf = create_config();

    cr_assert_eq(get_commande_path(env, "diff", &conf), NULL);
}

Test(get_commande, not)
{
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    conf_t conf = create_config();

    cr_assert_eq(get_commande_path(env, "./dsfgfd", &conf), NULL);
}

Test(mem_util, test1)
{
    char *env_b[] = {"PWD=/", "PATH=/usr/bin/", "cool", NULL};
    env_t *env = load_env(env_b);
    conf_t conf = create_config();

    cr_assert_eq(get_commande_path(env, "./dsfgfd", &conf), NULL);
    realloc_env(env);
}
