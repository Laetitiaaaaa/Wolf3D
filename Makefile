# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleblond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 08:56:17 by jleblond          #+#    #+#              #
#    Updated: 2019/03/14 08:56:22 by jleblond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= wolf3d

BASE_SRC		= main.c										\

INIT_SRC		= init.c										\

BASE_PATH		= ./src/

INIT_PATH		= ./src/init/

OBJ_PATH		= ./OBJ

SRCS			=	$(addprefix $(BASE_PATH), $(BASE_SRC))			\
					$(addprefix $(INIT_PATH), $(INIT_SRC))			\

INC				= -I ./includes

LIB				= -L ./libft/

GCC				= gcc

FLAGS			= -Wall -Wextra -Werror

OBJS			= $(addprefix $(OBJ), $(SRCS:.c=.o))

MAKELIB			= make re -C libft/

LIBFT			= -Llibft/ -lft

LIBMLX			= -L ./libui -lSDL2 -lSDL2_image

FRAME			= -framework OpenGL -framework AppKit

RANDOM			= $$

%.o: %.c ./includes/wolf3d.h
	@$(GCC) $(INC) -o $@ -c $< $(FLAGS)

$(NAME): $(OBJS)
	@$(GCC) -o $@ `sdl2-config --cflags --libs` $(OBJS) $(LIB) $(LIBFT) $(LIBMLX) $(FRAME) $(FLAGS)

all : $(NAME)

clean :
	@rm -rf $(OBJS) ; echo "Obj Cleaned"

fclean : clean
	@rm -rf $(NAME) ; echo "Exec Cleaned"

re : fclean all

relibft :
	$(MAKELIB)

.PHONY : all clean fclean re
