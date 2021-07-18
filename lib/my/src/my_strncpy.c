/*
** EPITECH PROJECT, 2020
** my_strncpy
** File description:
** copie n byte from a dest string to a dest string
*/

char *my_strncpy(char *dest, char *src, int n)
{
    int i = 0;

    while (src[i] && i < n) {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
        dest[i] = '\0';
    return dest;
}
