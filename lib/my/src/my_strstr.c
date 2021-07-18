/*
** EPITECH PROJECT, 2020
** my_strstr
** File description:
** find a string in a bigger and return the pointeur to the first occurence
*/

static int check(int index, char *str, char *to_find)
{
    int i = index;
    int j = 0;

    while (to_find[j]) {
        if (str[i] != to_find[j]) {
            return (-1);
        }
        i++;
        j++;
    }
    return index;
}

char *my_strstr(char *str, char *to_find)
{
    int find = -1;

    if (to_find[0] == '\0')
        return str;
    for (int i = 0; str[i]; i++) {
        find = -1;
        if (str[i] == to_find[0])
            find = check(i, str, to_find);
        if (find != -1)
            return (str + find);
    }
    return (0);
}
