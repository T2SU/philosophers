# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 15:55:21 by smun              #+#    #+#              #
#    Updated: 2021/07/29 15:54:40 by smun             ###   ########.fr        #
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
	srcs/logic/main \
	srcs/logic/simulator \
	srcs/logic/philo \
	srcs/logic/philo_life \
	srcs/logic/philo_fork \
	srcs/logic/printer \
	srcs/logic/context \
	srcs/logic/utils \
	srcs/logic/monitor \
	srcs/variation/sync_mutex
FILES_SRC = $(addsuffix .c, $(FILES))
FILES_OBJ = $(FILES_SRC:.c=.o)

NAME = philo

all : $(NAME)

clean :
	rm -rf $(FILES_OBJ)
	rm -rf $(NAME).dSYM

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(FILES_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean fclean re $(NAME)
