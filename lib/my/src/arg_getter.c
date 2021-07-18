/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** use macro to get depending of the type the value
*/

#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>
#include <unistd.h>
#include "my.h"
#include "my_printf.h"

void get_int_length(char i, va_list ap, long long *nb)
{
    SUPER_VARG((i == HH_F), *nb, int, ap);
    SUPER_VARG((i == H_F), *nb, int, ap);
    SUPER_VARG((i == -1), *nb, int, ap);
    SUPER_VARG((i == L_F), *nb, long, ap);
    SUPER_VARG((i == LL_F), *nb, long long, ap);
    SUPER_VARG((i == Z_F), *nb, ssize_t, ap);
    SUPER_VARG((i == J_F), *nb, intmax_t, ap);
    SUPER_VARG((i == T_F), *nb, ptrdiff_t, ap);
}

void get_uint_length(char i, va_list ap, unsigned long long *nb)
{
    SUPER_VARG((i == HH_F), *nb, unsigned int, ap);
    SUPER_VARG((i == H_F), *nb, unsigned int, ap);
    SUPER_VARG((i == -1), *nb, unsigned int, ap);
    SUPER_VARG((i == L_F), *nb, unsigned long, ap);
    SUPER_VARG((i == LL_F), *nb, unsigned long long, ap);
    SUPER_VARG((i == Z_F), *nb, size_t, ap);
    SUPER_VARG((i == J_F), *nb, uintmax_t, ap);
    SUPER_VARG((i == T_F), *nb, ptrdiff_t, ap);
}
