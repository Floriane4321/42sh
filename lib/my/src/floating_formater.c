/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** format the floating point number
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

void extract_float(unsigned long long *int_part, unsigned long long *dec_part,
        long double reminder)
{
    *int_part = (unsigned long long)reminder;
    reminder -= *int_part;
    reminder *= 1e9;
    *dec_part = (unsigned long long)reminder;
}

char *write_float(unsigned long long int_part, unsigned long long dec_part,
        int *size_int, int *size_dec)
{
    char *buff = my_calloc(*size_dec + *size_int + 5, sizeof(char));
    for (int i = 0; i <= *size_int; i++) {
        buff[*size_int - i] = int_part % 10 + '0';
        int_part /= 10;
    }
    buff[(*size_int) += 1] = '.';
    *size_int += 1;
    for (int i = 0; i <= *size_dec; i++) {
        (buff + *size_int)[*size_dec - i] = dec_part % 10 + '0';
        dec_part /= 10;
    }
    return (buff);
}

char *double_for(formating_t *form, va_list ap)
{
    unsigned long long int_part, dec_part;
    int size_int = 0;
    int size_dec = 0;
    int size_final;
    long double reminder = va_arg(ap, double);
    int is_neg = (reminder < 0) ? 1 : 0;
    char *buff, *final;
    padding_t pad = {0, 0, 0, 0, 0, 0};

    extract_float(&int_part, &dec_part, reminder);
    NB_DIGIT_INT(size_int, int_part);
    NB_DIGIT_INT(size_dec, dec_part);
    buff = write_float(int_part, dec_part, &size_int, &size_dec);
    size_final = my_strlen(buff);
    final = my_calloc(get_pad(form, &pad, size_final, 0) + 10, sizeof(char));
    final[0] = neg_place(&is_neg, form);
    my_strcpy(final + pad.bf + is_neg, buff);
    put_padding(form, &pad, 0, final + is_neg);
    return (final);
}
