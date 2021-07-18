CC = gcc
SRC = ./arg_getter.c \
      ./base_formater.c \
      ./convert_base.c \
      ./floating_formater.c \
      ./formater.c \
      ./formatting_getter_printf.c \
      ./interger_formater.c \
      ./Makefile \
      ./my_calloc.c \
      ./my_compute_power_rec.c \
      ./my_compute_square_root.c \
      ./my_getnbr_base.c \
      ./my_getnbr.c \
      ./my_printf.c \
      ./my_putchar.c \
      ./my_puterr.c \
      ./my_putnbr_base.c \
      ./my_put_nbr.c \
      ./my_putstr.c \
      ./my_revstr.c \
      ./my_showmem.c \
      ./my_strcat.c \
      ./my_strcmp.c \
      ./my_strcpy.c \
      ./my_strdup.c \
      ./my_strlen.c \
      ./my_strncat.c \
      ./my_strncmp.c \
      ./my_strncpy.c \
      ./my_strstr.c \
      ./my_memcpy.c \
      ./my_str_to_word_array.c \
      ./string_formater.c \
      ./my_sprintf.c \
      ./my_print_errf.c
OBJ = $(SRC:.c=.o)
CFLAGS += -Wall -Wextra -fno-builtin
IFLAGS = -I../include

all: $(OBJ)

.c.o:
	$(CC) -c $*.c $(CFLAGS) $(IFLAGS) -o $@
clean:
	rm -rf *.o

fclean:
	$(MAKE) clean
re: fclean all

.PHONY: all clean fclean re
