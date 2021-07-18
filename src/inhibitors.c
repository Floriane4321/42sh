/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** inhibitors
*/

char is_inhibited(char *line, int i)
{
    char inib_status = 0;

    if (i - 1 < 0)
        return 0;
    i--;
    while (i >= 0 && line[i] == '\\') {
        i--;
        inib_status = !inib_status;
    }
    return inib_status;
}

void shift_str_left(char *str, int i)
{
    while (str[i]) {
        str[i] = str[i + 1];
        i++;
    }
}

char get_special_char(char *str, int i)
{
    switch (str[i]) {
    case 'n':
        return '\n';
    case 't':
        return '\t';
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'v':
        return '\v';
    case 'f':
        return '\f';
    case 'r':
        return '\r';
    case '\\':
        return '\\';
    default:
        return str[i];
    }
}

void remove_inhibitors(char *str)
{
    int i = 0;

    while (str[i]) {
        if (str[i] == '\\') {
            str[i] = get_special_char(str, i + 1);
            shift_str_left(str, i + 1);
        }
        i++;
    }
}