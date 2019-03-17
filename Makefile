# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llejeune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/15 16:31:36 by llejeune          #+#    #+#              #
#    Updated: 2019/03/15 16:33:19 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= wolf3d

BASE_SRC		= main.c loop.c convert.c dda.c	draw_background.c draw_2d.c \

INIT_SRC		= init.c map.c									\

BASE_PATH		= ./src/

INIT_PATH		= ./src/init/

HEADER			= ./includes/wolf3d.h

OBJ_PATH		= ./OBJ

SRCS			=	$(addprefix $(BASE_PATH), $(BASE_SRC))			\
					$(addprefix $(INIT_PATH), $(INIT_SRC))			\

INC				= -I ./includes -I ./libft -I ./libui/SDL2/

GCC				= gcc

FLAGS			= -Wall -Wextra -Werror

OBJS			= $(addprefix $(OBJ), $(SRCS:.c=.o))

MAKELIB			= make re -C libft/

LIBSDL			= -L ./libui -lSDL2 -lSDL2_image

FRAME			= -framework OpenGL -framework AppKit

LIBFTA			= libft/libft.a

all : $(NAME)

$(NAME): $(OBJS)
	$(GCC) -o $@ `sdl2-config --cflags --libs` $(OBJS) $(LIBFTA) $(LIBSDL) $(FRAME) $(FLAGS)

%.o: %.c $(HEADER) $(LIBFTA)
	$(GCC) $(INC) -o $@ -c $< $(FLAGS)

$(LIBFTA): FORCE
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
