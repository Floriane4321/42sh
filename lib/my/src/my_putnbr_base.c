/*
** EPITECH PROJECT, 2020
** my_putnbr_base
** File description:
** display the number in the given base
*/

void my_putchar(char c);

static void print_final_number(int nb_array[32], int index, char const *base)
{
    for (int i = index - 1; i >= 0; i--) {
        my_putchar(base[nb_array[i]]);
    }
}

static long check_neg(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        return -nb;
    }
    return nb;
}

int my_putnbr_base(int nbr, char const *base)
{
    int base_int = 0;
    int reminder_array[32] = {0};
    int i = 0;
    long result = 1;
    long nb = check_neg(nbr);

    while (base[base_int])
        base_int++;
    while (result != 0) {
        result = nb / base_int;
        reminder_array[i] = nb % base_int;
        nb = result;
        i++;
    }
    print_final_number(reminder_array, i, base);
    return (1);
}
