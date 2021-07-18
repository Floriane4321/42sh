/*
** EPITECH PROJECT, 2020
** my_compute_square_root
** File description:
** the computation to find the square root of a number
*/

int my_compute_square_root(int nb)
{
    int a = nb / 2;

    if (nb <= 0)
        return (0);
    if (nb == 1)
        return (1);
    while (a * a != nb) {
        if (a == 0)
            break;
        a--;
    }
    return (a);
}
