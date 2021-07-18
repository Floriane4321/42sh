/*
** EPITECH PROJECT, 2020
** my_putstr
** File description:
** my_putstr.c 08:58 01/10
*/

void my_putchar(char c);

void my_putstr(char const *str)
{
    int i = 0;

    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}
