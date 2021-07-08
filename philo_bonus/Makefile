# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 15:55:21 by smun              #+#    #+#              #
#    Updated: 2021/07/07 21:19:28 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debug compilation
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

# Compilation option for Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -pthread
endif

INC = -I.
FILES = \
	main \
	simulator \
	philo \
	printer \
	child \
	utils \
	monitor \
	sync_semaphore \
	child_process
FILES_SRC = $(addsuffix .c, $(FILES))
FILES_OBJ = $(FILES_SRC:.c=.o)

NAME = philo_bonus

all : $(NAME)

clean :
	rm -rf $(FILES_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(FILES_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean fclean re $(NAME) debug
