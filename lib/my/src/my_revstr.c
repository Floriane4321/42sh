/*
** EPITECH PROJECT, 2020
** my_revstr
** File description:
** reverse a str
*/

#include <unistd.h>

char *my_revstr(char *str)
{
    char temp;
    int i = 0;
    int n = 0;

    while (str[n])
        n++;
    while (str[n / 2 + i]) {
        temp = str[i];
        str[i] = str[n - 1- i];
        str[n - 1 - i] = temp;
        i++;
    }
    return (str);
}
