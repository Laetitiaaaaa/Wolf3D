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

INIT_SRC		= init.c map.c									\

BASE_PATH		= ./src/

INIT_PATH		= ./src/init/

OBJ_PATH		= ./OBJ

SRCS			=	$(addprefix $(BASE_PATH), $(BASE_SRC))			\
					$(addprefix $(INIT_PATH), $(INIT_SRC))			\

INC				=  -I ./libft -I ./includes -I ./libui/SDL2/

GCC				= gcc

FLAGS			= -Wall -Wextra -Werror

OBJS			= $(addprefix $(OBJ), $(SRCS:.c=.o))

MAKELIB			= make re -C libft/

LIBFT			= libft/libft.a

LIBMLX			= -L ./libui -lSDL2 -lSDL2_image

FRAME			= -framework OpenGL -framework AppKit

HEADER			= wolf3d.h

RANDOM			= $$

all : $(NAME)

$(NAME): $(OBJS)
	$(GCC) -o $@ `sdl2-config --cflags --libs` $(OBJS) $(LIBFT) $(LIBMLX) $(FRAME) $(FLAGS) $(INC)

%.o: %.c $(HEADER) $(LIBFT)
	$(GCC) $(FLAGS) -o $@ -c $< $(INC)

$(LIBFT): FORCE
	make -C ./libft

FORCE:

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

relibft:
	$(MAKELIB)

.PHONY: all clean fclean re
