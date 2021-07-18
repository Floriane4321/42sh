/*
** EPITECH PROJECT, 2020
** my_strncat
** File description:
** contate to string for n char
*/

int my_strlen(char const *str);

char *my_strncat(char *dest, char const *src, int nb)
{
    int end_dest = my_strlen(dest);
    int i = 0;

    while (src[i] && i < nb) {
        dest[end_dest + i] = src[i];
        i++;
    }
    if (i < nb)
        dest[i + end_dest] = '\0';
    return dest;
}
