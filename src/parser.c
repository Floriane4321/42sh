/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** parse the line to be exec
*/

#include <stdlib.h>
#include <string.h>
#include "../include/my.h"
#include "../include/minishell.h"

char *get_arg(char const *str, int *size, char *chars, parser_t *conf)
{
    int i;
    char *arg;
    char last_char = ' ';

    for (i = 0; str[i] && !(char_is(str[i], chars, conf) &&
            last_char != '\\'); i++) {
        last_char = str[i];
    }
    arg = my_strndup(str, i);
    *size = i;
    return (arg);
}

char *get_arg_match(char const *str, int *size, char *match)
{
    int i;
    char *arg;
    int len_tmp = my_strlen(match);
    char last_char = ' ';

    for (i = 0; str[i] && my_strncmp(str + i, match, len_tmp) &&
            last_char != '\\'; i++)
        last_char = str[i];
    arg = my_strndup(str, i);
    *size = i;
    return (arg);
}

list_t *parse_line(char *line, int size_line, char *chars, int need_free)
{
    list_t *list = NULL;
    int cur = 0;
    int len_tmp;
    char *arg;
    parser_t conf = {0, 1, ' '};

    for (cur = 0; line[cur] && char_is(line[cur], chars, &conf); cur++);
    while (cur < size_line) {
        arg = get_arg(line + cur, &len_tmp, chars, &conf);
        add_data_list(&list, arg);
        cur += len_tmp + 1;
        if (cur >= size_line)
            break;
        while (line[cur] && char_is(line[cur], chars, &conf))
            cur++;
    }
    reverse_list(&list);
    if (need_free)
        free(line);
    return (list);
}

list_t *parse_line_match(char *line, int len_line, char *ma, int need_free)
{
    list_t *list = NULL;
    int cursor = 0;
    int len_tmp = my_strlen(ma);
    char *arg;

    for (cursor = 0; line[cursor] && my_strncmp(line, ma, len_tmp) == 0;
            cursor++);
    while (cursor < len_line) {
        arg = get_arg_match(line + cursor, &len_tmp, ma);
        add_data_list(&list, arg);
        cursor += len_tmp + 1;
        if (cursor >= len_line)
            break;
        cursor += my_strlen(ma);
    }
    reverse_list(&list);
    if (need_free)
        free(line);
    return (list);
}

char **list_to_tab(list_t *list)
{
    char **res;
    int list_size = get_list_size(list);
    int i = 0;

    res = malloc(sizeof(char *) * (list_size + 1));
    for (list_t *tmp = list; tmp; tmp = tmp->next) {
        res[i++] = tmp->data;
    }
    res[i] = NULL;
    return (res);
}
