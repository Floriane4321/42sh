/*
** EPITECH PROJECT, 2020
** my_showmem
** File description:
** show the memoire from a pointeur for n size
*/

void my_putchar(char c);
int my_putnbr_base(int nb, char const *base);

static void show_address(int i)
{
    int nb_zero = 0;
    int result = i;

    while (result >= 1) {
        result /= 16;
        nb_zero ++;
    }
    if (i == 0)
        nb_zero ++;
    for (int z = 8; z > nb_zero; z--) {
        my_putchar('0');
    }
    my_putnbr_base(i, "0123456789abcdef");
    my_putchar(':');
}

static void show_content_hex(char const *str, int i, int size)
{
    for (int j = 0; j < 16; j++) {
        if (j % 2 == 0)
            my_putchar(' ');
        if (i + j >= size) {
            my_putchar(' ');
            my_putchar(' ');
            continue;
        }
        if (str[i+ j] < 16)
            my_putchar('0');
        my_putnbr_base(str[i + j], "0123456789abcdef");
    }
    my_putchar(' ');
}

static void show_content_printable(char const *str, int i, int size)
{
    for (int j = 0; j < 16; j++) {
        if (i + j >= size)
            return;
        if (str[i + j] < ' ' || str[i + j] > '~')
            my_putchar('.');
        else
            my_putchar(str[i + j]);
    }
}

int my_showmem(char const *str, int size)
{
    for (int i = 0; i < size; i += 16) {
        show_address(i);
        show_content_hex(str, i, size);
        show_content_printable(str, i, size);
        my_putchar('\n');
    }
    return 0;
}
