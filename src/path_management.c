/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** search the right binarie in the path
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/minishell.h"
#include "../include/my.h"

int command_in_folder(char *command, char *folder)
{
    struct dirent *field_dir;
    DIR *dir = opendir(folder);

    if (dir == NULL)
        return (0);
    while ((field_dir = readdir(dir)) != NULL) {
        if (my_strcmp(field_dir->d_name, command) == 0) {
            closedir(dir);
            return (1);
        }
    }
    closedir(dir);
    return (0);
}

char *get_pwd(env_t *env)
{
    for (int i = 0; i < env->nb_var; i++) {
        if (my_strncmp(env->env_var[i], "PWD=", 4) == 0)
            return (env->env_var[i] + 4);
    }
    return ("");
}

char *direct_exec(char *command, env_t *env)
{
    char *res;

    if (command[0] == '/')
        res = my_sprintf("%s", command);
    else
        res = my_sprintf("%s/%s", get_pwd(env), command);
    return (check_cmd(res, command));
}

char *get_commande_path(env_t *env, char *cmd, conf_t *config)
{
    char *path = NULL;
    char *res;

    if ((cmd[0] == '.' && cmd[1] == '/') || str_contain(cmd, '/') != -1)
        return (direct_exec(cmd, env));
    for (list_t *i = env->list_path; i; i = i->next)
        if (command_in_folder(cmd, i->data)) {
            path = i->data;
            break;
        }
    if (path == NULL) {
        my_errprintf("%s: Command not found.\n", cmd);
        config->last_status = 1;
        return (NULL);
    }
    if (path[my_strlen(path) - 1] == '/')
        res = (my_sprintf("%s%s", path, cmd));
    else
        res = (my_sprintf("%s/%s", path, cmd));
    return (check_cmd(res, cmd));
}
