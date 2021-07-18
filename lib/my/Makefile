CC = gcc
SRC_DIR = ./src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -fno-builtin
IFLAGS = -I./include/
NAME = libmy.a

all: $(NAME)

$(NAME): $(SRC)
	cd $(SRC_DIR) && $(MAKE)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ../
	mkdir -p ../../include/
	cp include/my.h ../../include/
	cp include/my_printf.h ../../include/
$(OBJ): 
	cd $(SRC_DIR) && $(MAKE)

clean:
	rm -rf $(SRC_DIR)/*.o

fclean:
	$(MAKE) clean
	rm -rf $(NAME)
	rm -rf ../$(NAME)

re: fclean
	$(MAKE)

.PHONY: clean fclean re
