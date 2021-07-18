/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** tests_globbings
*/

#include <criterion/criterion.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"

Test(globbings, _glob_line)
{
    char *globbed;
    char *expected1 = "ABC.txt Component.jsx Component.react";
    char *expected2 = " abc.txt bar file1 file2 file3 foo";
    int len = strlen(expected1) + strlen(expected2);
    char *expected = calloc(len + 1, sizeof(char));
    int glob_no_match = 0;
    conf_t conf;

    expected = strcat(expected, expected1);
    expected = strcat(expected, expected2);
    chdir("./tests/globbing_tests_dir/");
    globbed = glob_line(strdup("*"), ALLOC_TRUE, &glob_no_match, &conf);
    cr_assert_str_eq(globbed, expected);
    free(expected);
    free(globbed);
}

Test(globbings, _glob_borders)
{
    char *line = "the glob pattern is *here*";
    char *line2 = "[this_is_a_full_globbing]";

    cr_assert_eq(get_glob_start(line), 20);
    cr_assert_eq(get_glob_end(line + 20), 6);
    cr_assert_eq(get_glob_start(line2), 0);
    cr_assert_eq(get_glob_end(line2 + 0), strlen(line2));
}