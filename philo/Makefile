CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = -I.
FILES = \
main
FILES_SRC = $(addsuffix .c, $(FILES))
FILES_OBJ = $(FILES_SRC:.c=.o)

NAME = philo

all : $(NAME)

clean :
	rm -rf $(FILES_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(FILES_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(FILES_OBJ)

.PHONY: all clean fclean re $(NAME)
