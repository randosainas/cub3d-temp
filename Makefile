#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:57:50 by lpetit            #+#    #+#              #
#    Updated: 2024/08/12 13:22:16 by lpetit           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= cub3D

CC		= cc

SRCS 	= ./srcs/helper.c ./srcs/map_init.c ./srcs/main.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
			./srcs/map_check.c

LIB_DIR = ./libft

LIB		= $(LIB_DIR)/libft.a

INCLUDES = ./includes

OBJS	= $(SRCS:.c=.o)

FLAGS	= -Wall -Wextra -Werror

#Colors:
GREEN		=	\e[92;5;118m
GRAY		=	\e[33;2;37m
CURSIVE		=	\e[33;3m
RESET		=	\e[0m

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(NAME):	$(OBJS)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	$(CC) $(FLAGS) -I$(INCLUDES) $(OBJS) $(LIB) -o $(NAME)
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

%.o: %.c
	$(CC) $(FLAGS) -I$(INCLUDES) -c "$<" -o "$@"

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean:	clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all