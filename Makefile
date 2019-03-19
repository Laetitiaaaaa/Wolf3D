# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llejeune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/18 19:20:02 by llejeune          #+#    #+#              #
#    Updated: 2019/03/19 10:45:39 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

INC_DIR = $(shell find includes -type d) $(shell find libft -type d) $(shell find ~/.brew/include/SDL2 -type d)

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = obj

SRC = loop.c \
	  main.c \
	  menu.c \
	  init.c \
	  map.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

LIBS = SDL2 SDL2_image ft

LIB_DIR = ./libft \
		  ~/.brew/lib \
		  ./libraries/SDL2_image \

FRAMEWORK = OpenGL AppKit

CC = gcc

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

IFLAG = $(foreach dir, $(INC_DIR), -I$(dir) )

CFLAG = -Wall -Wextra -Werror

LFLAG = $(foreach dir, $(LIB_DIR), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) )

all: $(NAME)

relib:
	@make re -C libft

$(NAME): $(OBJ)
	@make -C libft
	@echo "Compiling $(NAME) !"
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(IFLAG) $(LFLAG)

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@echo "Compiling $< ... \c"
	@$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)
	@echo "DONE"

clean:
	@make clean -C libft
	@echo "Cleaning the project"
	@rm -f $(OBJ)

fclean:
	@make clean
	@echo "Fcleaning the project"
	@rm $(NAME)

re:
	@make fclean
	@echo "Restarting the compilation"
	@make $(NAME)

