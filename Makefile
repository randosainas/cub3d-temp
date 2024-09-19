#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:57:50 by lpetit            #+#    #+#              #
#    Updated: 2024/09/19 15:10:31 by rsainas          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= cub3D

CC		= cc

SRCS 	= ./srcs/helper.c ./srcs/map_init.c ./srcs/main.c \
./gnl/get_next_line.c ./gnl/get_next_line_utils.c ./srcs/render.c \
./srcs/map_check.c ./srcs/closed.c \
./srcs/init_graphics.c ./srcs/events.c ./srcs/draw_map.c \
./srcs/cast_rays.c ./srcs/cast_helper.c ./srcs/key_hook.c \
./srcs/init_player.c

LIB_DIR = ./libft

LIB		= $(LIB_DIR)/libft.a

INCLUDES = ./includes

OBJS	= $(SRCS:.c=.o)

FLAGS	= -Wall -Wextra -Werror -g

MLX_DIR = ./minilibx-linux

X = -L $(MLX_DIR) -lmlx -L /usr/X11R6/lib -lXext -lX11 -lm -lz -I$(MLX_DIR) -Ilmlx

#X		= 	-L $(MLX_DIR) -lm -lmlx -lX11 -lz -I$(MLX_DIR) -Ilmlx
#X		= 	-L ${MLX_DIR} -lmlx -lXext -lX11 -lm -lz -I${MLX_DIR} -Ilmlx

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
	$(CC) $(FLAGS) -I$(INCLUDES) $(OBJS) $(LIB) $(X) -o $(NAME)
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
