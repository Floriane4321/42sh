/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** color_prompt
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/minishell.h"
#include "../include/my.h"

void prompt_cwd(char *cwd)
{
    int len = my_strlen(cwd);
    int start = 0;

    start = len - 1;
    for (int i = len - 1; cwd[i] != '/'; i--)
        start--;
    if (cwd[start] == '/')
        start++;
    if (cwd[len - 1] == '/')
        start = 0;
    my_printf("%s%s", cwd + start, RESET_COLOR);
    free(cwd);
}

void prompt_selec(env_t *env)
{
    char *buff = NULL;
    char *home = get_var("HOME", env);

    buff = getcwd(buff, (size_t)0);
    if (home != NULL && !my_strcmp(home, buff)) {
        my_printf("~%s", RESET_COLOR);
        free(buff);
    } else
        prompt_cwd(buff);
}

void color_prompt(conf_t *conf, env_t *env)
{
    if (conf->last_status == 0)
        my_putstr(PROMPT);
    else
        my_putstr(ERR_PROMPT);
    prompt_selec(env);
    if (conf->is_git) {
        my_printf("%sgit:(%s%s%s)%s", GIT_BLUE, GIT_RED,
        conf->git_branch, GIT_BLUE, RESET_COLOR);
    }
}
