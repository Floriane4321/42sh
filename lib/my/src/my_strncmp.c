/*
** EPITECH PROJECT, 2020
** my_strncmp
** File description:
** compare two string for n size
*/

int my_strlen(char const *str);

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;
    int taille_str1 = my_strlen(s1);
    int taille_str2 = my_strlen(s2);

    if (taille_str1 < taille_str2 && taille_str1 < n) {
        return (-1);
    } else if (taille_str2 < taille_str1 && taille_str2 < n) {
        return (1);
    }
    while (s1[i] && s2[i] && i < n) {
        if (s1[i] < s2[i])
            return (-1);
        if (s2[i] < s1[i])
            return (1);
        i++;
    }
    return (0);
}
