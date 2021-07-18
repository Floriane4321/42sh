/*
** EPITECH PROJECT, 2020
** my_getnbr_base
** File description:
** from a string converte to an int depanding a base
*/

static int index_of_base(char c, char const *base)
{
    int i = 0;

    while (base[i] != c)
        i++;
    return i;
}

static int clean_nbr(const char *str, char clean_nb[32])
{
    int i_nb = 0;
    int neg = 0;

    for (int i = 0; str[i]; i++) {
        if (i_nb >= 32)
            return -1;
        if (str[i] == '-') {
            neg++;
            continue;
        } else if (str[i] == '+')
            continue;
        clean_nb[i_nb] = str[i];
        i_nb++;
    }
    clean_nb[i_nb] = '\0';
    return (neg);
}

static int return_res(unsigned long result, int is_neg)
{
    if (result > 2147483647)
        return (0);
    if (is_neg)
        return (-result);
    else
        return (result);
}

int my_getnbr_base(const char *str, const char *base)
{
    unsigned long result = 0;
    char clean_nb[32] = {0};
    int is_neg = 0;
    int base_int = 0;
    int res_clean = 0;

    while (base[base_int])
        base_int++;
    res_clean = clean_nbr(str, clean_nb);
    if (res_clean == -1)
        return 0;
    if (res_clean % 2 == 1)
        is_neg = 1;
    for (int i = 0; clean_nb[i]; i++)
        result = (result + index_of_base(clean_nb[i], base)) * base_int;
    return (return_res(result / base_int, is_neg));
}
