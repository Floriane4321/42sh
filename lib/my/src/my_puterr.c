/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** put str in the stderr
*/

#include <unistd.h>

void my_puterr(char const *err)
{
    int x = 0;

    while (err[x]) {
        write(2, &err[x], 1);
        x++;
    }
}
