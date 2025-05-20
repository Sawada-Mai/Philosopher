# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sawadamai <sawadamai@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:47:54 by msawada           #+#    #+#              #
#    Updated: 2025/05/17 22:01:39 by sawadamai        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c thred.c monitor.c init_philo.c check_argv.c actions.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -Wall -Wextra -Werror -O3 -pthread

HEADER = ./src/philo.h

SANITIZER = -fsanitize=thread

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all