/*
** EPITECH PROJECT, 2020
** my_printf
** File description:
** reproduce the printf fonction
*/

#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

int nb_occu(char c, char const *str, int *index)
{
    int oc = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            *index = i;
            oc++;
        }
    }
    return oc;
}

void init_formating(formating_t *formating)
{
    SET_ARRAY(6, formating->flags);
    formating->length = -1;
    formating->simple_type = 0;
    formating->type = 0;
    formating->width = -1;
    formating->precision = -1;
}

formating_t *create_formating_t(char const *format, int *index)
{
    formating_t *final = malloc(sizeof(formating_t));
    init_formating(final);
    int (*getter[5])(char const *, int *, formating_t *) = {get_flags,
        get_width, get_precision, get_length, get_type};

    *index += 1;
    init_formating(final);
    for (int i = 0; i < 5; i++) {
        getter[i](format, index, final);
    }
    return (final);
}

void handle_placeholder(char const *format, int *index, va_list ap)
{
    formating_t *formating = create_formating_t(format, index);
    char type_char[] = "dufexoscpab*n";
    char *temp;
    char *(*f_data_formater[])(formating_t *, va_list) = {int_for,
        uint_for, double_for, double_for, uint_hex_for,
        uint_oct_for, str_for, char_for, point_for,
        double_for, uint_bin_for, err_for};

    if (formating->simple_type == '%') {
        my_putchar('%');
        return;
    }
    for (int i = 0; i < my_strlen(type_char); i++) {
        if (formating->simple_type == type_char[i]) {
            temp = f_data_formater[i](formating, ap);
            write(1, temp, my_strlen(temp));
            free(temp);
        }
    }
    free(formating);
}

int my_printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%')
            handle_placeholder(format, &i, ap);
        else
            my_putchar(format[i]);
    }
    va_end(ap);
    return (1);
}
