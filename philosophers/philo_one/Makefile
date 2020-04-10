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

SRC= main.c ft_utils.c init_sem.c parse_args.c print_state.c ft_utils2.c threads.c
NAME = philo_one

all: $(NAME)

$(NAME): 
	gcc  $(SRC) -o $(NAME)
	@echo "Done."

clean:
	@echo "Cleaning object files..."
	@echo "Done."

fclean: clean
	@echo "Cleaning Library..."
	@$(RM) $(NAME)
	@echo "Done."

re: fclean all 

