/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** handling of the signal
*/

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "../include/minishell.h"
#include "../include/my.h"

int has_been_signal(int flag)
{
    static int last_stat = 0;
    int tmp;

    if (flag == 0) {
        tmp = last_stat;
        last_stat = 0;
        return (tmp);
    }
    last_stat = flag;
    return (last_stat);
}

static void handler(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    has_been_signal(sig);
}

int setup_signal_handling(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        exit(84);
    return (0);
}
