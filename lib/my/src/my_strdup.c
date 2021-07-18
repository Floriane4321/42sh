/*
** EPITECH PROJECT, 2020
** my_strup
** File description:
** return a new allocated string from a const one
*/

#include <stdlib.h>

char *my_strdup(char const *str)
{
    int size = 1;
    char *result;

    while (str[size - 1])
        size++;
    result = malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++)
        result[i] = str[i];
    return (result);
}
