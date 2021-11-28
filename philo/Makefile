# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 14:22:51 by skienzle          #+#    #+#              #
#    Updated: 2021/11/28 19:06:24 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra  # -pthread -fsanitize=thread
RM = rm -rf

SDIR = src
SRC = main.c utils.c malloc.c free.c exit.c init.c 

ODIR = objs
OBJ = $(patsubst %.c, %.o, $(SRC))

$(NAME): $(addprefix $(SDIR)/, $(SRC))
	@$(CC) $(CFLAGS) -c $^
	@mkdir -p $(ODIR)
	mv $(OBJ) $(ODIR)
	@$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJ)) -o $(NAME)
	@echo $(NAME) created!\\n

all: $(NAME)

clean:
	$(RM) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	make -C ../philo_bonus

.PHONY: all clean fclean re bonus