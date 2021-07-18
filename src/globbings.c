/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** globbings
*/

#include <glob.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"

char *glob_pattern(char *pattern, int *glob_no_match)
{
    glob_t pglob;
    char *str;
    int len = 0;

    pattern = escape_quoted_chars(pattern);
    glob(pattern, GLOB_TILDE | GLOB_NOMAGIC | GLOB_TILDE_CHECK, NULL, &pglob);
    for (int i = 0; i < (int)pglob.gl_pathc; i++)
        len += strlen(pglob.gl_pathv[i]) + 1;
    str = calloc(len, sizeof(char));
    for (int i = 0; i < (int)pglob.gl_pathc; i++) {
        str = strcat(str, pglob.gl_pathv[i]);
        if (i + 1 < (int)pglob.gl_pathc)
            str = strcat(str, " ");
    }
    free(pattern);
    if (pglob.gl_pathc < 1)
        *glob_no_match += 1;
    globfree(&pglob);
    return str;
}

char *replace_globbing(gdata_t g_data, conf_t *conf)
{
    int size = strlen(g_data.line) + strlen(g_data.globbed) + 1;
    char *str = calloc(size, sizeof(char));
    char *globbing_next;

    str = strncpy(str, g_data.line, g_data.start);
    str = strcat(str, g_data.globbed);
    if (g_data.line[g_data.start + g_data.end]) {
        if (*(g_data.glob_no_match) < 1)
            globbing_next = glob_line(g_data.line + g_data.start + g_data.end,
            ALLOC_FALSE, g_data.glob_no_match, conf);
        else
            globbing_next = strdup("");
        str = realloc(str, size + strlen(globbing_next));
        str = strcat(str, globbing_next);
        free(globbing_next);
    }
    if (g_data.is_allocated)
        free(g_data.line);
    return str;
}

void pglob_err(char *line, int p_start, conf_t *conf)
{
    int i = p_start;

    for (; i > 0 && line[i] != ';' && line[i] != '|' && line[i] != '&'; i--);
    while (line[i] == ';' || line[i] == '|' || line[i] == '&' ||
    line[i] == '\t' || line[i] == ' ')
        i++;
    for (; line[i] != ' ' && line[i] != '\t'; i++)
        write(2, &(line[i]), 1);
    dprintf(2, ": No match.\n");
    conf->last_status = 1;
}

char *glob_line(char *line, char is_allocated, int *glob_no_match, conf_t *c)
{
    char *pattern;
    gdata_t g_data = {line, line, 0, 0, is_allocated, glob_no_match};

    if (!str_has_glob_char(g_data.line))
        return g_data.globbed;
    g_data.start = get_glob_start(g_data.line);
    g_data.end = get_glob_end(line + g_data.start);
    pattern = strndup(g_data.line + g_data.start, g_data.end);
    g_data.globbed = glob_pattern(pattern, g_data.glob_no_match);
    if (*(g_data.glob_no_match))
        pglob_err(g_data.line, g_data.start, c);
    g_data.line = replace_globbing(g_data, c);
    remove_spe_char(g_data.line, '\"');
    return g_data.line;
}
