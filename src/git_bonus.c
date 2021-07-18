/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** git_bonus
*/

#include "minishell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void redirect_outputs(int *fd_err, int (*fd)[2])
{
    int devnull = open("/dev/null", O_RDWR);

    (void)fd_err;
    pipe(*fd);
    dup2((*fd)[1], STDOUT_FILENO);
    dup2(devnull, STDERR_FILENO);
    close(devnull);
}

void reset_outputs(int old[3], int fd[2])
{
    dup2(old[1], STDOUT_FILENO);
    close(fd[1]);
    dup2((old[2]), STDERR_FILENO);
}

void *free_n_close(char *res, int fd)
{
    free(res);
    close(fd);
    return NULL;
}

char *get_gitbranch(conf_t *config, env_t *env)
{
    int fd[2];
    char *res = malloc(sizeof(char));
    int old[3] = {dup(STDIN_FILENO), dup(STDOUT_FILENO), dup(STDERR_FILENO)};
    int offset = 0;

    redirect_outputs(&(old[2]), &fd);
    under_shell(env, "git branch --show-current", config);
    reset_outputs(old, fd);
    if (config->last_status)
        return free_n_close(res, fd[0]);
    while (read(fd[0], res + offset, 1) > 0) {
        if (res[offset] == '\n')
            res[offset] = '\0';
        offset++;
        res = realloc(res, sizeof(char) * offset + 1);
        res[offset] = '\0';
    }
    close(fd[0]);
    return res;
}

void get_git(conf_t *conf, env_t *env)
{
    int old_last_status = conf->last_status;

    if (conf->git_branch)
        free(conf->git_branch);
    conf->git_branch = get_gitbranch(conf, env);
    conf->is_git = !(conf->last_status);
    conf->last_status = old_last_status;
}
