/*
** EPITECH PROJECT, 2020
** my_put_nbr
** File description:
** description
*/

void my_putchar(char c);

static int get_nbr_digits(long nb)
{
    int result = 0;

    while (nb >= 10) {
        result++;
        nb = nb / 10;
    }
    return (result);
}

static long my_pow(long a, long b)
{
    long temp = 1;
    long i = b;

    while (i >= 1) {
        temp *= a;
        i--;
    }
    return (temp);
}

static long check_nb(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        return (-(long)nb);
    }
    if (nb == 0) {
        my_putchar('0');
        return (0);
    }
    return ((long)nb);
}

int my_put_nbr(int n)
{
    int nb_digits;
    long nb;

    nb = check_nb(n);
    if (n == 0) {
        return (0);
    }
    nb_digits = get_nbr_digits(nb);
    while (nb_digits >= 0) {
        my_putchar(48 + nb / my_pow(10, nb_digits));
        nb = nb % my_pow(10, nb_digits);
        nb_digits--;
    }
    return (0);
}
