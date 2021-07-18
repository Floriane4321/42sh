/*
** EPITECH PROJECT, 2020
** convert_base
** File description:
** take number in a base and convert it to another base
*/

#include <stdlib.h>

int my_strlen(char const *str);

static int index_of_base(char c, char const *base)
{
    int i = 0;

    while (base[i] != c)
        i++;
    return i;
}

static int get_nb_digit(int nb, int base_to_nb)
{
    int i = 1;
    while (nb >= base_to_nb) {
        nb /= base_to_nb;
        i++;
    }
    return i;
}

static char *to_base(int nb, int is_neg, const char *base_to)
{
    int base_to_nb = my_strlen(base_to);
    int taille = get_nb_digit(nb, base_to_nb);
    char *result;
    int i = 1;

    if (is_neg)
        taille++;
    result = malloc(sizeof(char) * (taille + 1));
    while (nb != 0) {
        result[taille - i] = base_to[nb % base_to_nb];
        nb = nb / base_to_nb;
        i++;
    }
    if (is_neg)
        result[0] = '-';
    result[taille] = '\0';
    return result;
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    unsigned long result = 0;
    int base_from_nb = my_strlen(base_from);
    int i = 0;
    int is_neg = 0;

    if (nbr[0] == '-') {
        is_neg = 1;
        i = 1;
    }
    for (; nbr[i]; i++)
        result = (result + index_of_base(nbr[i], base_from)) * base_from_nb;
    result /= base_from_nb;
    if (result > 2147483647)
        result = 0;
    return to_base(result, is_neg, base_to);
}
