/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** header file for the minishell
*/

#ifndef HEADER_MINISHELL
#define HEADER_MINISHELL

#define IS_AL(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define IS_NUM(c) (c >= '0' && c <= '9')

#define G_STR(x) ((char *)(x->data))
#define G_ALIAS(x) ((alias_t *)(x->data))

#define PROMPT "\e[1m\e[32m➜  \e[0m\e[1m\e[36m"
#define ERR_PROMPT "\e[1m\e[31m➜  \e[0m\e[1m\e[36m"
#define RESET_COLOR "\e[39m\e[0m "
#define GIT_BLUE "\033[1;34m"
#define GIT_RED "\033[1;31m"

#define GLOB_CHARS "*?[{]}"
#define GLOB_SEPS "|><;& "

#define ALLOC_TRUE 1
#define ALLOC_FALSE 0

#define _GNU_SOURCE 1

#define NOT_GIT "fatal: not a git repository"

#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

#define OPEN_FLAG (O_CREAT | O_WRONLY)

typedef struct list {
    char *data;
    struct list *next;
} list_t;

typedef struct env {
    char **env_var;
    int allocated_var;
    int nb_var;
    int index_path;
    list_t *list_path;
} env_t;

struct pipe_s {
    int p[2];
};

typedef struct glob_data {
    char *line;
    char *globbed;
    int start;
    int end;
    char is_allocated;
    int *glob_no_match;
} gdata_t;

typedef struct backstick_list {
    struct backstick_list *p;
    int is_cmd;
    char *content;
    char *result;
    struct backstick_list *n;
} bs_list_t;

typedef struct parser {
    int in_gil;
    int check_in;
    char last_char;
} parser_t;

typedef struct pipe_inf {
    struct pipe_s *pipes;
    int out;
    int in;
    int c_p;
    int file_in;
    int file_out;
} pipe_inf_t;

typedef struct set_s {
    char *name;
    char *var;
    struct set_s *next;
}set_t;

typedef struct conf {
    int is_git;
    char *git_branch;
    int termined;
    int last_status;
    list_t *last_dir;
    int nb_child;
    int is_tty;
    list_t *list_alias;
    set_t *set;
    char *cmd;
    pipe_inf_t *pi_inf;
    FILE *history;
    int line_count_hist;
} conf_t;

typedef struct alias {
    char *cmd_name;
    char *rem;
} alias_t;

// list utilities
list_t *add_data_list(list_t **begin, char *data);
void clean_list(list_t *list);
void reverse_list(list_t **begin);
int get_list_size(list_t *list);
void clean_args_tab(char **args_tab);

// parser
int get_end_arg(char const *str);
list_t *parse_line(char *line, int size_line, char *chars, int need_free);
list_t *parse_line_match(char *line, int len_line, char *ma, int need_free);
char **list_to_tab(list_t *list);

// environement variable
env_t *load_env(char *env[]);
char *get_path_dir(char *str, int *size);
list_t *create_path_list(env_t *env);
int get_var_index(char *var, env_t *env);
void clean_env(env_t *env);
char *get_var(char *var, env_t *env);
int setenv_err(char **args);

// path management
int command_in_folder(char *command, char *folder);
char *get_commande_path(env_t *env, char *command, conf_t *conf);
char *get_pwd(env_t *env);
char *update_pwd(env_t *env);
int update_path(char *changed_var, env_t *env);
char *get_pwd(env_t *env);

// execution
int process_execution(list_t *args, char *cmd, env_t *env, conf_t *config);
int process_line(char *line, int size, env_t *env, conf_t *config);
int process_command_and(char *line, int size, env_t *env, conf_t *config);
int process_command_or(char *line, int size, env_t *env, conf_t *config);
int process_command(char *line, int size, env_t *env, conf_t *config);

// built-in exec
int builtin_execution(list_t *list_args, env_t *env, conf_t *config);
int is_builtin(char *command);

// stream
int process_pipe(char *line, int size, env_t *env, conf_t *config);
void exec_pipe(conf_t *config, int del_std);
void handle_after_exec_pipe(int *ret, conf_t *config, pid_t pid);

// get_input_bloc
int create_tmp_file(char *end);

// redirection
int process_redirection(char *line, env_t *env, conf_t *conf, int *err);

// usr interaction
int prompt(env_t *env);
void color_prompt(conf_t *conf, env_t *env);
int skip_line(char **line, conf_t *config);

//config
conf_t create_config(void);
conf_t create_config_his(env_t *env);
int add_to_history(char *line, env_t *env, conf_t *conf);

// mem_utilities
void realloc_env(env_t *env);

//error_utilities
int print_and_return(char *message, int return_val);
char *check_cmd(char *path_commande, char *command);
int handle_return(int ret, conf_t *config);

// string utilities
int str_contain(char *str, char c);
int char_is(char c, char *str, parser_t *conf);
char *my_strndup(char const *src, int size);
int compte_char(char *str, char match);
void clean_whitespaces(char *str);

// stack utilities
void push(list_t **list, char *data);
char *pop(list_t **list);

// globbings
char *glob_line(char *line, char is_allocated, int *glob_no_match, conf_t *c);
int get_glob_end(char *line);
int get_glob_start(char *line);
char is_glob_separator(char *line, int i);
int str_has_glob_char(char *line);
int is_glob_char(char *line, int i);

// inhibitors
void remove_inhibitors(char *str);
char is_inhibited(char *line, int i);
void shift_str_left(char *str, int i);

// backsticks
char *process_backsticks(char *line, conf_t *config, env_t *env);
bs_list_t *create_bslist(char *line);

// balanced chars
char is_balanced(char *line, char c, conf_t *conf);
char skip_q_mark(char *line, int *i);
void remove_spe_char(char *line, char c);

char *escape_quoted_chars(char *str);

// handle_guillemet
int remove_guillemet(list_t *list);

// signal_handle
int setup_signal_handling();
int has_been_signal(int flag);

// under_shell
int preparation_under_shell(env_t *env, char *line, conf_t *config);
int under_shell(env_t *env, char *line, conf_t *config);

// parentheses
char *parcing_parentheses(char *line, int len, conf_t *config);
char *replace_point_in_parentheses(char *line, char replace, char c);
int count_parentheses(char *line, char c);

// set
int my_set(char **args, env_t *env, conf_t *config);
set_t *execution_set(set_t *now, set_t *list, char **args, int nb);
set_t *find_current_node(set_t *set, char *arg);
set_t *add_end(set_t *list, set_t *cell);
void disp_env_set(set_t *set);
int count_rows(char **str);
int count_cmp(char **args, int i);
set_t *add_node_set(char *name, char *var, set_t *set);
char *get_value_set(set_t *set, char *arg);
int check_equal(char **str);
char **parcing_set(char **arg);

// line expanding
char *modify_line(char *line, conf_t *config, env_t *env, int *mod_err);
char *expand_line(char *line, int *size, conf_t *config);

// git bonus
void get_git(conf_t *conf, env_t *env);

// dollar_vars
char *get_dollar_vars(char *line, int *undefined_var, conf_t *c, env_t *env);

// dollar_var_utils
int get_d_end(char *line);
int get_d_start(char *line, int i);
char *get_local_var(char *name, conf_t *c);
char *get_var_value(char *var_name, conf_t *conf, env_t *env);
void var_err(char *name, conf_t *conf, int *undefined_var);
// alias
alias_t *is_alias(char *cmd, conf_t *config);
int print_alias(conf_t *conf, char **args);

// my_repeat
int is_num(char *str);
char *my_concat(char **av);
// foreach array utils
void clean_foreach_str(char *str);
char **str_to_2darray(char *str);
#endif
