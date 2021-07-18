/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** get input by bloc
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "../include/minishell.h"
#include "../include/my.h"

char *get_input(FILE *fd, int *exit)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, fd);
    if (read < 1 && line) {
        free(line);
        line = NULL;
        *exit = 1;
    }
    return (line);
}

int create_tmp_file(char *end)
{
    FILE *file = tmpfile();
    int end_len = strlen(end);
    int exit = 0;
    char *input;

    if (!file)
        return (-1);
    do {
        dprintf(1, "? ");
        input = get_input(stdin, &exit);
        if (input && strncmp(input, end, end_len) != 0)
            fprintf(file, "%s", input);
    } while (!exit && input && strncmp(input, end, end_len) != 0);
    if (exit == 1) {
        fclose(file);
        return (-1);
    }
    fseek(file, 0, SEEK_SET);
    return (fileno(file));
}
