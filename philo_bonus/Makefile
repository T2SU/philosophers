# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 15:55:21 by smun              #+#    #+#              #
#    Updated: 2021/07/30 03:00:14 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debug compilation
ifeq ($(DEBUG),1)
	CFLAGS += -g -DDEBUG=1
endif

# Compilation option for Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -pthread
endif

INC = -I.
FILES = \
	srcs/main \
	srcs/simulator \
	srcs/philo \
	srcs/philo_life \
	srcs/printer \
	srcs/context \
	srcs/context_process \
	srcs/context_died_monitor \
	srcs/context_full_monitor \
	srcs/utils \
	srcs/monitor \
	srcs/sync_semaphore
FILES_SRC = $(addsuffix .c, $(FILES))
FILES_OBJ = $(FILES_SRC:.c=.o)

NAME = philo_bonus

all : $(NAME)

bonus : all

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

.PHONY: all clean fclean re bonus $(NAME)
