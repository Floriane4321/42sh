/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** test_usr_interaction
*/

#include "minishell.h"
#include <criterion/criterion.h>

Test(_skip_line, invalid_cases)
{
    conf_t conf;
    char *line1 = strdup("missing second quote mark \"\n");

    cr_assert_eq(skip_line(&line1, &conf), 1);
    free(line1);
    line1 = strdup("missing second magic quote`");
    cr_assert_eq(skip_line(&line1, &conf), 1);
    free(line1);
}

Test(_skip_line, valid_cases)
{
    conf_t conf;
    char *line1 = strdup("ls \"*\"");

    cr_assert_eq(skip_line(&line1, &conf), 0);
    free(line1);
    line1 = strdup("ls `ls`");
    cr_assert_eq(skip_line(&line1, &conf), 0);
    free(line1);
}