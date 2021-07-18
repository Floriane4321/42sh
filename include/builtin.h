/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** description
*/

#ifndef HEADER_BUILT_IN
#define HEADER_BUILT_IN

#include "minishell.h"

typedef struct built_in {
    char const *command;
    int (*func)(char **, env_t *, conf_t *);
} built_in_t;

//first file
int my_cd(char **args, env_t *env, conf_t *config);
int my_exit(char **args, env_t *env, conf_t *config);
int my_env(char **args, env_t *env, conf_t *config);
int my_setenv(char **args, env_t *env, conf_t *config);
int my_unsetenv(char **args, env_t *env, conf_t *config);

//seconde file
int my_alias(char **args, env_t *env, conf_t *config);
int error_pipe(char **args, env_t *env, conf_t *config);

//buit_in folder
int my_where(char **args, env_t *env, conf_t *config);
int my_which(char **args, env_t *env, conf_t *config);
int my_echo(char **args, env_t *env, conf_t *config);
int my_if(char **args, env_t *env, conf_t *config);
int my_repeat(char **args, env_t *env, conf_t *config);
int my_set(char **args, env_t *env, conf_t *config);
int my_history(char **args, env_t *env, conf_t *config);
int my_foreach(char **args, env_t *env, conf_t *config);

const int nb_built_in = 15;
const built_in_t builts_in[] = {{"cd", my_cd}, {"exit", my_exit},
    {"setenv", my_setenv}, {"unsetenv", my_unsetenv}, {"env", my_env},
    {"alias", my_alias}, {"error_on_pipe", error_pipe}, {"where", my_where},
    {"echo", my_echo}, {"which", my_which}, {"if", my_if},
    {"repeat", my_repeat}, {"set", my_set}, {"foreach", my_foreach},
    {"history", my_history}};
#endif
