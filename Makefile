# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 19:32:34 by fhenrich          #+#    #+#              #
#    Updated: 2023/03/30 12:31:58 by fhenrich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= c++

CFLAGS	= -Wall -Werror -Wextra  -std=c++98 -pedantic -Wunused -Wshadow -g

NAME	= webserv

SRC		= src/main.cpp

OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
