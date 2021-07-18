/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** description
*/

int my_strlen(char const *str);

static int check_num(char const *str, long num, int nb_digits)
{
    int nb_neg = 0;

    if (nb_digits > 10 || num > 2147483648)
        return (-1);
    for (int i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9')
            break;
        if (str[i] == '-')
            nb_neg++;
    }
    if (nb_digits > 10 || num > 2147483648)
        return (-1);
    else if (nb_digits > 10 ||  (num > 2147483647 && nb_neg % 2 == 0))
        return (-1);
    return (nb_neg);
}

static int check_char(char c, long *result, int *nb_digits)
{
    static int in_nb = 0;

    if ((c < '0' || c > '9' )&& in_nb == 1)
        return 1;
    if (c >= '0' && c <= '9') {
        *result = *result * 10 + c - 48;
        in_nb = 1;
        (*nb_digits)++;
    }
    return 0;
}

int my_getnbr(char const *str)
{
    long result = 0;
    int nb_digits = 0;

    for (int i = 0; str[i]; i++) {
        if (check_char(str[i], &result, &nb_digits) == 1)
            break;
    }
    if (check_num(str, result, nb_digits) == -1)
        return (0);
    else if (check_num(str, result, nb_digits) % 2 == 1)
        return (-result);
    return (result);
}
