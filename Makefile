# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 14:22:51 by skienzle          #+#    #+#              #
#    Updated: 2021/10/21 20:06:49 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
RM = rm -rf

IDIR = inc
INC = philosophers.h

SDIR = src
SRC = main.c ft_malloc.c

ODIR = objs
OBJ = $(patsubst %.c, %.o, $(SRC))

$(NAME):$(addprefix $(SDIR)/, $(SRC))
	$(CC) $(CFLAGS) -c $^
	mkdir -p $(ODIR)
	mv $(OBJ) $(ODIR)
	$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJ)) -o $(NAME)
	@echo $(NAME) created!\\n

all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus