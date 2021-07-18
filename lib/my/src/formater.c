/*
** EPITECH PROJECT, 2020
** my_printf
** File description:
** formate to the stdout the given data
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

char *err_for(formating_t *form, va_list ap)
{
    char *res = my_calloc(25, sizeof(char));
    int i = 0;
    (void)ap;

    res[i++] = '%';
    for (int j = 0; j < 6; j++)
        if (form->flags[j])
            res[i++] = form->flags[j];
    if (form->width > 0)
        i += put_int_in_buf(res + i, form->width);
    if (form->precision > 0) {
        res[i++] = '.';
        i += put_int_in_buf(res + i, form->precision);
    }
    res[i++] = form->type;
    return (res);
}

int get_pad(formating_t *form, padding_t *pad, int size_nb, int offset)
{
    int width_diff = (form->width != -1) ? form->width - size_nb - offset : 0;

    if ((form->flags[1] || form->flags[2]) && offset != 1)
        width_diff--;
    if (form->flags[0])
        pad->a_s = (width_diff > 0 && !form->flags[3]) ? width_diff : 0;
    else {
        pad->b_0 = (width_diff > 0 && form->flags[3]) ? width_diff : 0;
        pad->b_s = (width_diff > 0 && !form->flags[3]) ? width_diff : 0;
    }
    pad->bf = pad->b_0 + pad->b_s;
    pad->af = pad->a_0 + pad->a_s;
    return (size_nb + pad->b_s + pad->a_s + pad->b_0 + pad->a_0 );
}

void put_padding(formating_t *form, padding_t *pad, int offset, char *buff)
{
    int i = offset;
    int end_nb;

    for (; i < pad->b_s; i++)
        buff[i] = ' ';
    for (; i < pad->b_0; i++)
        buff[i] = '0';
    while (buff[i++]);
    end_nb = --i;
    for (; i < pad->a_0 + end_nb; i++)
        buff[i] = '0';
    for (; i < pad->a_s + end_nb; i++)
        buff[i] = ' ';
}

char neg_place(int *is_neg, formating_t *form)
{
    if (*is_neg) {
        return ('-');
    }
    if (form->flags[1]) {
        *is_neg = 1;
        return ('+');
    }
    if (form->flags[2]) {
        *is_neg = 1;
        return (' ');
    }
    return ('\0');
}
