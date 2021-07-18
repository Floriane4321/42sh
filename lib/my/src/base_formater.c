/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** format the base
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

char *convert_long_base(unsigned long long nb, char *base)
{
    unsigned long long tmp = nb;
    unsigned long long base_to = my_strlen(base);
    int taille = 0;
    char *result;

    while (tmp >= base_to) {
        tmp /= base_to;
        taille++;
    }
    result = malloc(sizeof(char) * (taille + 2));
    if (nb == 0)
        result[0] = '0';
    for (int i = 0; nb > 0; i++) {
        result[taille - i] = base[nb % base_to];
        nb /= base_to;
    }
    result[taille + 1] = '\0';
    return result;
}

char *uint_hex_for(formating_t *form, va_list ap)
{
    unsigned long long nb;
    int size_nb = 0;
    int is_neg = 0;
    char *buff, *nb_base;
    char *base = (form->type == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
    padding_t pad = {0, 0, 0, 0, 0, 0};

    get_uint_length(form->length, ap, &nb);
    nb_base = convert_long_base(nb, base);
    size_nb = my_strlen(nb_base) + ((form->flags[5]) ? 2 : 0);
    buff = my_calloc(get_pad(form, &pad, size_nb, 0) + 5, sizeof(char));
    *(buff + pad.bf) = neg_place(&is_neg, form);
    if (form->flags[5]) {
        my_strcpy(buff + pad.bf + is_neg, (form->type == 'x') ? "0x" : "0X");
        is_neg += 2;
    }
    my_strcpy(buff + pad.bf + is_neg, nb_base);
    free(nb_base);
    put_padding(form, &pad, 0, buff);
    return (buff);
}

char *uint_oct_for(formating_t *form, va_list ap)
{
    unsigned long long nb;
    int size_nb = 0;
    int is_neg = 0;
    char *buff, *nb_base;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    get_uint_length(form->length, ap, &nb);
    nb_base = convert_long_base(nb, "01234567");
    size_nb = my_strlen(nb_base) + ((form->flags[5]) ? 1 : 0);
    buff = my_calloc(get_pad(form, &pad, size_nb, 0) + 5, sizeof(char));
    *(buff + pad.bf) = neg_place(&is_neg, form);
    if (form->flags[5]) {
        *(buff + pad.bf + is_neg) = '0';
        is_neg += 1;
    }
    my_strcpy(buff + pad.bf + is_neg, nb_base);
    free(nb_base);
    put_padding(form, &pad, 0, buff);
    return (buff);
}

char *point_for(formating_t *form, va_list ap)
{
    form->flags[5] = '#';
    form->length = LL_F;
    form->simple_type = 'x';
    form->type = 'x';
    return (uint_hex_for(form, ap));
}

char *uint_bin_for(formating_t *form, va_list ap)
{
    unsigned long long nb;
    int size_nb = 0;
    int is_neg = 0;
    char *buff, *nb_base;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    get_uint_length(form->length, ap, &nb);
    nb_base = convert_long_base(nb, "01");
    size_nb = my_strlen(nb_base);
    buff = my_calloc(get_pad(form, &pad, size_nb, 0) + 5, sizeof(char));
    *(buff + pad.bf) = neg_place(&is_neg, form);
    my_strcpy(buff + pad.bf + is_neg, nb_base);
    free(nb_base);
    put_padding(form, &pad, 0, buff);
    return (buff);
}
