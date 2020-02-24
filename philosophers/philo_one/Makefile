# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bothilie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 13:23:17 by bothilie          #+#    #+#              #
#    Updated: 2019/10/10 13:48:13 by bothilie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_one

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

SRC= main.c ft_utils.c

OBJ=$(SRC:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) $(SRC)

all: $(NAME)

clean:
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean, fclean

