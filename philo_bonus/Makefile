# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skienzle <skienzle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/28 18:58:04 by skienzle          #+#    #+#              #
#    Updated: 2021/11/29 01:25:07 by skienzle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra  -pthread -O3
RM = rm -rf

SDIR = src
SRC = main_bonus.c utils_bonus.c init_bonus.c exit_bonus.c simulation_bonus.c

ODIR = objs
OBJ = $(patsubst %.c, %.o, $(SRC))

$(NAME): $(addprefix $(SDIR)/, $(SRC))
	@$(CC) $(CFLAGS) -c $^
	@mkdir -p $(ODIR)
	@mv $(OBJ) $(ODIR)
	@$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJ)) -o $(NAME)
	@echo $(NAME) created!\\n

all: $(NAME)

clean:
	@$(RM) $(ODIR)
	@echo $(ODIR) removed!\\n

fclean: clean
	@$(RM) $(NAME)
	@echo $(NAME) removed!\\n

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus