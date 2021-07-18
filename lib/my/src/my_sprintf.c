/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** my_sprintf
*/

#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

char *handle_placeholder_sprintf(char const *format, int *index, va_list ap)
{
    formating_t *formating = create_formating_t(format, index);
    char type_char[] = "dufexoscpab*n";
    char *temp;
    char *(*f_data_formater[])(formating_t *, va_list) = {int_for,
        uint_for, double_for, double_for, uint_hex_for,
        uint_oct_for, str_for, char_for, point_for,
        double_for, uint_bin_for, err_for};

    if (formating->simple_type == '%')
        return my_strdup("%");
    for (int i = 0; i < my_strlen(type_char); i++) {
        if (formating->simple_type == type_char[i]) {
            temp = f_data_formater[i](formating, ap);
            free(formating);
            return (temp);
        }
    }
    free(formating);
}

char *char_to_string(char c)
{
    char *res = my_calloc(2, sizeof(char));
    res[0] = c;
    return (res);
}

char *tab_to_string(char **tab, int size)
{
    int i;
    int total_size = 0;
    char *final;

    for (i = 0; i < size; i++)
        total_size += my_strlen(tab[i]);
    final = my_calloc(total_size + 2, sizeof(char));
    i = 0;
    for (int j = 0; j < size; j++) {
        for (int k = 0; tab[j][k]; k++)
            final[i++] = tab[j][k];
        free(tab[j]);
    }
    free(tab);
    return (final);
}

char *my_sprintf(const char *format, ...)
{
    va_list ap;
    char **tab = malloc(sizeof(char *) * (my_strlen(format) + 2));
    int index = 0;

    va_start(ap, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%')
            tab[index++] = handle_placeholder_sprintf(format, &i, ap);
        else
            tab[index++] = char_to_string(format[i]);
    }
    va_end(ap);
    return (tab_to_string(tab, index));
}
