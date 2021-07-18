
vpath %.c src/
vpath %.c src/input_usr/
vpath %.h include/
vpath %.c src/built_in/

CC = gcc
MAIN = ./src/main.c
SRC =	environement.c \
      env_utilities.c \
      list_utilities.c \
      path_management.c \
      usr_interaction.c \
      built_in_exec.c \
      execution.c \
      built_in.c \
      built_in2.c \
      redirection.c \
      pipe.c \
      parser.c \
      config.c \
      stack.c \
      string_utilities.c \
      error_handler.c \
      handle_guillemet.c \
      mem_utilities.c   \
      signal_handle.c \
      get_input_bloc.c \
      globbings.c       \
      globbing_utils.c  \
      color_prompt.c    \
      inhibitors.c      \
      quote_marks.c     \
      main.c		\
      glob_spe_chars_utils.c \
      my_where.c	\
	  my_which.c \
	  my_echo.c \
	  history.c \
	parentheses.c	\
	  cleaning.c \
	  line_expansion.c \
	under_shell.c	\
	parentheses_utile.c	\
	set.c	\
	set_utile.c \
	parcing_set.c	\
      backsticks.c      \
      git_bonus.c	\
	my_if.c	\
	my_repeat.c \
	dollar_var.c	\
	dollar_var_utils.c	\
	alias.c	\
	foreach_array_utils.c \
	my_foreach.c \

SRC_TEST = $(wildcard tests/*.c)

SRC_TEST += $(shell find ./src -type f -name "*.c" | grep -v "main.c")

OBJ = $(SRC:.c=.o)
OBJ += $(MAIN:.c=.o)

ALL_OBJ =	$(patsubst %.c, $(OBJECT)/%.o, $(SRC))


LIB_FILE = ./lib/libmy.a
CFLAGS = -Wall -Wextra -fno-builtin -g3
IFLAGS = -I./include/
LFLAGS = -L./lib/ -lmy

NAME = 42sh
OBJECT =	obj

all: $(NAME)

$(NAME): $(OBJECT) $(ALL_OBJ) $(LIB_FILE)
	@$(CC) -o $(NAME) $(ALL_OBJ) $(IFLAGS) $(LFLAGS) $(CFLAGS) -g
	@echo  -e "\e[32mlinking compliete\e[39m"

.c.o:
	$(CC) -c $*.c $(CFLAGS) $(IFLAGS) -o $@

$(LIB_FILE):
	$(MAKE) -C ./lib/my/ fclean
	$(MAKE) -C ./lib/my/

clean: clean_tests
	rm -rf $(OBJECT)/*.o

tests_run: fclean $(SRC_TEST) $(LIB_FILE)
	$(CC) -o unit_tests $(SRC_TEST) $(IFLAGS) $(LFLAGS) $(CFLAGS) -lcriterion --coverage
	./unit_tests
	gcovr -b --exclude tests
	gcovr --exclude tests

clean_tests:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf unit_tests

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJECT)
re: fclean all

.PHONY: clean fclean re all

$(OBJECT):
	@echo -e "\e[95mOBJ Directory Generate\e[0m"
	@mkdir -p $(OBJECT)

$(OBJECT)/%.o   : %.c
	@$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS) -g
	@echo -e "\t\e[36mCompilate \e[3;97;4m$@\e[00m; \e[1;92mSUCCES\e[00m"

