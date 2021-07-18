/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** format integer
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

int put_int_in_buf(char *buff, int nb)
{
    int si_nb = 0;

    NB_DIGIT_INT(si_nb, nb);
    for (int i = 0; i <= si_nb; i++) {
        buff[si_nb - i] = nb % 10 + '0';
        nb /= 10;
    }
    return (si_nb + 1);
}

char *int_for(formating_t *form, va_list ap)
{
    long long nb = 0;
    int si_nb = 0;
    int is_neg;
    char *buff;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    get_int_length(form->length, ap, &nb);
    is_neg = (nb < 0) ? 1 : 0;
    nb = (nb < 0) ? -nb : nb;
    NB_DIGIT_INT(si_nb, nb);
    buff = my_calloc(get_pad(form, &pad, si_nb + 1, is_neg) + 5, sizeof(char));
    buff[0] = neg_place(&is_neg, form);
    for (int i = 0; i <= si_nb; i++) {
        (buff + pad.bf + is_neg)[si_nb - i] = nb % 10 + '0';
        nb /= 10;
    }
    put_padding(form, &pad, 0, buff + is_neg);
    return (buff);
}

char *uint_for(formating_t *form, va_list ap)
{
    unsigned long long nb;
    int si_nb = 0;
    int is_neg = 0;
    char *buff;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    get_uint_length(form->length, ap, &nb);
    NB_DIGIT_INT(si_nb, nb);
    buff = my_calloc(get_pad(form, &pad, si_nb + 1, 0) + 5, sizeof(char));
    buff[0] = neg_place(&is_neg, form);
    for (int i = 0; i <= si_nb; i++) {
        (buff + pad.bf + is_neg)[si_nb - i] = nb % 10 + '0';
        nb /= 10;
    }
    put_padding(form, &pad, 0, buff + is_neg);
    return (buff);
}

char *char_for(formating_t *form, va_list ap)
{
    char c;
    char *buff;
    int size_str = 1;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    c = va_arg(ap, int);
    buff = my_calloc(get_pad(form, &pad, size_str, 0) + 2, sizeof(char));
    my_strncpy(buff + pad.bf, &c, 1);
    put_padding(form, &pad, 0, buff);
    return (buff);
}
