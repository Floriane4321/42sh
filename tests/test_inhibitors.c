/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** test_inhibitors
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "minishell.h"

Test(inhibitors, basic)
{
    char *str = strdup("hello\\ ");

    remove_inhibitors(str);
    cr_assert_str_eq(str, "hello ");
    free(str);
    str = strdup("hello\\\\");
    remove_inhibitors(str);
    cr_assert_str_eq(str, "hello\\");
    free(str);
}

Test(inhibitors, special_chars)
{
    char *str = strdup("hello\\t");

    remove_inhibitors(str);
    cr_assert_str_eq(str, "hello\t");
    free(str);
    str = strdup("hello\\n");
    remove_inhibitors(str);
    cr_assert_str_eq(str, "hello\n");
    free(str);
    str = strdup("hello\\y");
    remove_inhibitors(str);
    cr_assert_str_eq(str, "helloy");
    free(str);
}