/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** unit test for the parser
*/

#include <criterion/criterion.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(parser, test1)
{
    char *test = "ls resss  \t  cool";
    char *final[] = {"ls", "resss", "cool"};
    list_t *res = parse_line(test, my_strlen(test), " \t", 0);

    for (int i = 0; i < 3; i++) {
        cr_assert_str_eq(res->data, final[i]);
        res = res->next;
    }
}

Test(parser, test2)
{
    char *test = "ls resss cool";
    char *final[] = {"ls", "resss", "cool"};
    list_t *res = parse_line(test, my_strlen(test), " \t", 0);
    char **tab = list_to_tab(res);

    for (int i = 0; i < 3; i++) {
        cr_assert_str_eq(tab[i], final[i]);
    }
    cr_assert(tab[3] == NULL);
}

Test(parser, test3)
{
    char *test = "ls resss cool; echo yooooo";
    char *final[] = {"ls resss cool", " echo yooooo"};
    list_t *res = parse_line(test, my_strlen(test), ";", 0);
    char **tab = list_to_tab(res);

    for (int i = 0; i < 2; i++) {
        cr_assert_str_eq(tab[i], final[i]);
    }
}
