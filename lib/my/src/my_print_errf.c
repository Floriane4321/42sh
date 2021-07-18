/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** my_printf to print on stderr
*/

#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

void my_putchar_err(char c)
{
    write(2, &c, 1);
}

void handle_placeholder_err(char const *format, int *index, va_list ap)
{
    formating_t *formating = create_formating_t(format, index);
    char type_char[] = "dufexoscpab*n";
    char *temp;
    char *(*f_data_formater[])(formating_t *, va_list) = {int_for,
        uint_for, double_for, double_for, uint_hex_for,
        uint_oct_for, str_for, char_for, point_for,
        double_for, uint_bin_for, err_for};

    if (formating->simple_type == '%') {
        my_putchar_err('%');
        return;
    }
    for (int i = 0; i < my_strlen(type_char); i++) {
        if (formating->simple_type == type_char[i]) {
            temp = f_data_formater[i](formating, ap);
            write(2, temp, my_strlen(temp));
            free(temp);
        }
    }
    free(formating);
}

int my_errprintf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%')
            handle_placeholder_err(format, &i, ap);
        else
            my_putchar_err(format[i]);
    }
    va_end(ap);
    return (1);
}
