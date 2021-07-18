/*
** EPITECH PROJECT, 2021
** B-PSU-210-LYN-2-1-42sh-nicolas.saclier
** File description:
** backticks
*/

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

bs_list_t *create_bsnode(char *content, int *pos, bs_list_t *p)
{
    bs_list_t *new = malloc(sizeof(bs_list_t));

    new->is_cmd = !(*pos % 2);
    *pos += 1;
    new->content = content;
    new->p = p;
    new->result = NULL;
    new->n = NULL;
    if (p)
        p->n = new;
    return new;
}

bs_list_t *create_bslist(char *line)
{
    int pos = 1;
    bs_list_t *first = NULL;
    bs_list_t *cur = NULL;
    char *tok = strtok(line, "`");

    if (tok)
        tok = strdup(tok);
    first = create_bsnode(tok, &pos, first);
    cur = first;
    while ((tok = (strtok(NULL, "`"))) != NULL) {
        tok = strdup(tok);
        cur = create_bsnode(tok, &pos, cur);
        if (cur->is_cmd)
            clean_whitespaces(cur->content);
    }
    return first;
}

char *exec_backstick(char *content, conf_t *config, env_t *env)
{
    int fd[2];
    char *res = malloc(sizeof(char));
    int old[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
    int offset = 0;

    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    config->last_status = under_shell(env, content, config);
    dup2(old[1], STDOUT_FILENO);
    close(fd[1]);
    while (read(fd[0], res + offset, 1) > 0) {
        if (res[offset] == '\n')
            res[offset] = ' ';
        offset++;
        res = realloc(res, sizeof(char) * offset + 1);
        res[offset] = '\0';
    }
    close(fd[0]);
    return res;
}

void destroy_bslist(bs_list_t *bslist)
{
    while (bslist) {
        free(bslist->content);
        if (bslist->is_cmd)
            free(bslist->result);
        if (bslist->p)
            free(bslist->p);
        if (bslist->n == NULL) {
            free(bslist);
            bslist = NULL;
        } else
            bslist = bslist->n;
    }
}

char *process_backsticks(char *line, conf_t *config, env_t *env)
{
    bs_list_t *bslist = create_bslist(line);
    bs_list_t *first = bslist;
    char *res = strdup("");

    while (bslist) {
        if (bslist->is_cmd && bslist->content) {
            bslist->result = exec_backstick(bslist->content, config, env);
            res = realloc(res, strlen(res) + strlen(bslist->result) + 1);
            res = strcat(res, bslist->result);
        } else if (bslist->content){
            res = realloc(res, strlen(res) + strlen(bslist->content) + 1);
            res = strcat(res, bslist->content);
        }
        bslist = bslist->n;
    }
    destroy_bslist(first);
    return res;
}
