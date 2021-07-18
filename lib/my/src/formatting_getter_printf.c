/*
** EPITECH PROJECT, 2020
** printf
** File description:
** with the base string extarct the form of the result
*/

#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

int get_flags(char const *format, int *index, formating_t *final)
{
    char flags_char[] = "-+ 0'#";
    int index_in_flags = 0;
    int i;

    for (i = *index; format[i]; i++) {
        if (nb_occu(format[i], flags_char, &index_in_flags) == 1) {
            final->flags[index_in_flags] = format[i];
            continue;
        }
        *index = i;
        return (0);
    }
    *index = i;
    return (-1);
}

int get_width(char const *format, int *index, formating_t *final)
{
    char c = format[*index];
    int result = 0;

    if (c < '0' || c > '9')
        return (0);
    while (c >= '0' && c <= '9') {
        result *= 10;
        result += c - '0';
        *index += 1;
        c = format[*index];
    }
    final->width = result;
    return (1);
}

int get_precision(char const *format, int *index, formating_t *final)
{
    int result = 0;
    char c = format[*index];

    if (c != '.')
        return (0);
    *index += 1;
    c = format[*index];
    while (c >= '0' && c <= '9') {
        result *= 10;
        result += c - '0';
        *index += 1;
        c = format[*index];
    }
    final->precision = result;
    return (1);
}

int get_length(char const *format, int *index, formating_t *final)
{
    char length_char[] = "hhllLzjt";
    int i_len = 0;
    int i = *index;

    if (nb_occu(format[i], length_char, &i_len) > 0) {
        final->length = i_len;
        i++;
    } else
        return (0);
    if (nb_occu(format[i], length_char, &i_len) > 0) {
        final->length = i_len;
        final->length = (final->length == H_F) ? HH_F : final->length;
        i++;
    } else
        final->length = (final->length == LL_F) ? L_F : final->length;
    *index = i;
    return (-1);
}

int get_type(char const *format, int *index, formating_t *final)
{
    char type_char[] = "\%\%diuufFeExXoosSccppaAbbnn";
    char type_char_simp[] = "\%dufexoscpabn";
    int i_type = -1;

    nb_occu(format[*index], type_char, &i_type);
    if (i_type == -1) {
        final->simple_type = '*';
        final->type = format[*index];
    } else {
        final->simple_type = type_char_simp[i_type / 2];
        final->type = type_char[i_type];
    }
    return (1);
}
