/*
** EPITECH PROJECT, 2020
** my_calloc
** File description:
** calloc fonction to allocate and set the mem to 0
*/

#include <stdlib.h>

void *my_calloc(int nb_item, int size)
{
    char *res = malloc(nb_item * size);

    for (int i = 0; i <nb_item * size; i++) {
        res[i] = 0;
    }
    return ((void *)res);
}
