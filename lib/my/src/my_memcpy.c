/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** copie a chunk of mem on another
*/

unsigned int my_memcpy(void *dst, void *src, unsigned int size)
{
    unsigned int i = 0;

    for (; i < size; i++)
        ((char *)dst)[i] = ((char *)src)[i];
    return (i);
}
