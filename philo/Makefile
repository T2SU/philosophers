# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 12:26:18 by smun              #+#    #+#              #
#    Updated: 2021/07/02 17:12:03 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = -I.
FILES = \
	main \
	fork \
	info \
	philo \
	time \
	utils \
	thread \
	print
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
