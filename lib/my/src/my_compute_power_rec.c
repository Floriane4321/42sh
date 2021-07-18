/*
** EPITECH PROJECT, 2020
** my_compute_power_rec
** File description:
** my_compute_power.c
*/

int my_compute_power_rec(int nb, int p)
{
    long result;

    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    result = nb * my_compute_power_rec(nb, p - 1);
    if (result > 2147483647 || result < -2147483648)
        return (0);
    else
        return ((int)result);
}
