/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handle the various possble error
*/

#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../include/my.h"
#include "../include/minishell.h"

int print_and_return(char *message, int return_val)
{
    my_errprintf("%s", message);
    return (return_val);
}

char *check_cmd(char *path_commande, char *command)
{
    struct stat path_stat;

    stat(path_commande, &path_stat);
    if (access(path_commande, X_OK) == 0 && !S_ISDIR(path_stat.st_mode))
        return (path_commande);
    if (S_ISDIR(path_stat.st_mode))
        my_errprintf("%s: Permission denied.\n", command, strerror(errno));
    else
        my_errprintf("%s: Command not found.\n", command);
    return (NULL);
}

void print_signal_err(int sign)
{
    char *msgs[] = {"Hangup", "", "Quit (core dumped)",
        "Illegal instruction (core dumped)", "Trace/BPT trap (core dumped)",
    "Abort (core dumped)", "Bus error (core dumped)",
    "Floating exception (core dumped)", "Killed", "User signal 1",
    "Segmentation fault (core dumped)", "User signal 2", "Broken pipe",
    "Alarm clock", "Terminated", "Stack limit exceeded", "", "",
    "Suspended (signal)", "Suspended", "Suspended (tty input)",
    "Suspended (tty output)", "", "Cputime limit exceeded (core dumped)",
    "Filesize limit exceeded (core dumped)", "Virtual time alarm",
    "Profiling time alarm", "", "Pollable event occured", "Power failure",
    "Bad system call (core dumped)"};

    if (sign > 31)
        return;
    my_errprintf("%s\n", msgs[sign - 1]);
}

int handle_return(int ret, conf_t *config)
{
    if (WIFSIGNALED(ret)) {
        print_signal_err(WTERMSIG(ret));
        config->last_status = 128 + WTERMSIG(ret);
    }
    if (WIFEXITED(ret))
        config->last_status = WEXITSTATUS(ret);
    return (config->last_status);
}
