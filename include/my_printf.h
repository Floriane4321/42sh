/*
** EPITECH PROJECT, 2020
** my_printf
** File description:
** header file for my_pritf
*/

#ifndef MY_PRINTF_HEADER
#define MY_PRINTF_HEADER
    #include <stdarg.h>
    #define SET_ARRAY(nb, arr) for (int i = 0; i < nb; arr[i++] = 0)

    #define SUPER_VARG(tst, nb, type, ap) (nb = (tst) ? va_arg(ap, type) : nb)
    #define NB_DIGIT_INT(i, nb) for (llong_t c_nb = nb; (c_nb /= 10) > 0; i++)
    typedef unsigned long long llong_t;
    enum length_field {
        HH_F = 0,
        H_F,
        L_F,
        LL_F,
        BL_F,
        Z_F,
        J_F,
        T_F,
    };

    typedef struct formating {
        char flags[6];
        int width;
        int precision;
        char length;
        char simple_type;
        char type;
    } formating_t;

    typedef struct padding {
        int b_s;
        int b_0;
        int a_s;
        int a_0;
        int bf;
        int af;
    } padding_t;

    int my_printf(char const *format, ...);
    char *int_for(formating_t *formating, va_list ap);
    char *uint_for(formating_t *formating, va_list ap);
    char *double_for(formating_t *formating, va_list ap);
    char *uint_hex_for(formating_t *formating, va_list ap);
    char *uint_oct_for(formating_t *formating, va_list ap);
    char *str_for(formating_t *formating, va_list ap);
    char *char_for(formating_t *formating, va_list ap);
    char *point_for(formating_t *formating, va_list ap);
    char *uint_bin_for(formating_t *formating, va_list ap);
    char *convert_long_base(unsigned long long nb, char *base);
    int nb_occu(char c, char const *str, int *index);
    int get_flags(char const *format, int *index, formating_t *final);
    int get_width(char const *format, int *index, formating_t *final);
    int get_precision(char const *format, int *index, formating_t *final);
    int get_length(char const *format, int *index, formating_t *final);
    int get_type(char const *format, int *index, formating_t *final);
    void get_int_length(char i, va_list ap, long long *nb);
    void get_uint_length(char i, va_list ap, unsigned long long *nb);
    int get_pad(formating_t *form, padding_t *pad, int size_nb, int offset);
    void put_padding(formating_t *form, padding_t *pad, int off, char *buff);
    char neg_place(int *is_neg, formating_t *form);
    char *err_for(formating_t *form, va_list ap);
    int put_int_in_buf(char *buff, int nb);
    formating_t *create_formating_t(char const *format, int *index);
    char *my_sprintf(const char *format, ...);
    int my_errprintf(const char *format, ...);

#endif
