/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** tests_bslist
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(backsticks, list_creation)
{
    char *str1 = strdup("ls `hello` world");
    bs_list_t *list = create_bslist(str1);

    cr_assert_str_eq(list->content, "ls ");
    cr_assert_str_eq(list->n->content, "hello");
    cr_assert_str_eq(list->n->n->content, " world");
    cr_assert_eq(list->is_cmd, 0);
    cr_assert_eq(list->n->is_cmd, 1);
    cr_assert_eq(list->n->n->is_cmd, 0);
    cr_assert_eq(list->n->n->n, NULL);
    free(str1);
    free(list->n);
    free(list->n->n);
    free(list);
}