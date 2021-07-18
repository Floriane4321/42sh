/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** format the string
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

char *char_to_oct(char c)
{
    int i = 0;
    char *final;

    NB_DIGIT_INT(i, c);
    final = my_calloc(i * 2 + 3, sizeof(char));
    final[0] = '\\';
    for (int i = 3; i > 0; i--) {
        final[i] = c % 8 + '0';
        c /= 8;
    }
    return (final);
}

char *put_special_char(char *buff, int str_len)
{
    char *final;
    char *temp;
    int nb_spe = 0;
    int i = 0;

    for (i = 0; buff[i]; i++)
        nb_spe += (buff[i] < 32 || buff[i] >= 127) ? 1 : 0;
    final = my_calloc(i + nb_spe * 4 + 1, sizeof(char));
    for (int j = 0; buff[str_len - i]; i--)
        if (buff[str_len - i] < 32 || buff[str_len - i] >= 127) {
            temp = char_to_oct(buff[str_len - i]);
            my_strcpy((final + j), temp);
            j += 4;
            free(temp);
        } else {
            final[j] = buff[str_len - i];
            j++;
        }
    free(buff);
    return (final);
}

char *str_for(formating_t *form, va_list ap)
{
    char *str, *buff;
    int size_str = 0;
    padding_t pad = {0, 0, 0, 0, 0, 0};
    int precision;

    str = va_arg(ap, char *);
    size_str = my_strlen(str);
    precision = (form->precision < size_str &&
            form->precision > 0) ? form->precision : size_str;
    buff = my_calloc(get_pad(form, &pad, size_str, 0) + 5, sizeof(char));
    my_strncpy(buff + pad.bf, str, precision);
    put_padding(form, &pad, 0, buff);
    if (form->type == 'S')
        return (put_special_char(buff, my_strlen(buff)));
    return (buff);
}
