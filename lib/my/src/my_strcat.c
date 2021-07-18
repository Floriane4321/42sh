/*
** EPITECH PROJECT, 2020
** my_strcat
** File description:
** take a string and put it at the end aof the des string
*/

int my_strlen(char const *str);

char *my_strcat(char *dest , char const *src)
{
    int end_dest = my_strlen(dest);
    int i = 0;

    while (src[i]) {
        dest[end_dest + i] = src[i];
        i++;
    }
    dest[i + end_dest] = '\0';
    return dest;
}
