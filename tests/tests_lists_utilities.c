/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** unit test for the list utilities
*/

#include <criterion/criterion.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(list_utils, test1)
{
    char *test = "ls resss   cool";
    list_t *res = parse_line(test, my_strlen(test), " \t", 0);

    clean_list(res);
}

Test(list_utils, test2)
{
    clean_list(NULL);
}

Test(list_utils, test3)
{

}
