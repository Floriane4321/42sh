/*
** EPITECH PROJECT, 2020
** my_strcpy
** File description:
** copie a string into in another
*/

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    if (!dest)
        return dest;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
