/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** tests file
*/

#include <criterion/criterion.h>
#include "../include/minishell.h"
#include "../include/my.h"

Test(err, test1)
{
    cr_assert_eq(check_cmd("./", "lib"), NULL);
}
