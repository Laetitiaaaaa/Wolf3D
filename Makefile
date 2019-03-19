# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llejeune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/19 16:52:44 by llejeune          #+#    #+#              #
#    Updated: 2019/03/19 17:05:35 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

INC_DIR = $(shell find includes -type d) $(shell find libft -type d) $(shell find ~/.brew/include/SDL2 -type d)

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = obj

SRC = loop.c \
	  convert.c \
	  dda.c \
	  draw_background.c \
	  draw_2d.c \
	  dda_horizontalwall.c \
	  main.c \
	  init_event.c\
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
	@echo "Cleaning the project ... \c"
	@rm -rf $(OBJ_DIR)
	@echo "DONE"

fclean:
	@make clean
	@echo "Fcleaning the project ... \c"
	@rm $(NAME)
	@echo "DONE"

re:
	@make fclean
	@echo "Restarting the compilation"
	@make $(NAME)

relib:
	@make re -C libft

image: ttf
	@mkdir libraries 2> /dev/null || true
	tar -xzf filetar/SDL2_image-2.0.4.tar.gz -C libraries
	cd libraries/SDL2_image-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries/SDL2_image-2.0.4
	make -C ./libraries/SDL2_image-2.0.4
	make -C ./libraries/SDL2_image-2.0.4 install
	mv ./libraries/SDL2_image-2.0.4/include/SDL2/SDL_image.h ./includes
	mv ./libraries/SDL2_image-2.0.4/lib/ ./libraries/SDL2_image
	rm -rf ./libraries/SDL2_image-2.0.4

ftype:
	@mkdir libraries 2> /dev/null ||true
	tar -xzf ./filetar/freetype-2.4.11.tar.gz -C libraries
	cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries/freetype-2.4.11
	make -C ./libraries/freetype-2.4.11
	make -C ./libraries/freetype-2.4.11 install
	mv ./libraries/freetype-2.4.11 ./libraries/freetype

ttf: ftype
	@mkdir libraries 2> /dev/null ||true
	tar -xzf ./filetar/SDL2_ttf-2.0.15.tar.gz -C libraries
	cd libraries/SDL2_ttf-2.0.15 ; ./configure --prefix=$(shell pwd)/libraries/SDL2_ttf-2.0.15
	make -C ./libraries/SDL2_ttf-2.0.15
	make -C ./libraries/SDL2_ttf-2.0.15 install
	mv ./libraries/SDL2_ttf-2.0.15/include/SDL2/SDL_ttf.h ./includes/
	mv ./libraries/SDL2_ttf-2.0.15/lib ./libraries/SDL2_ttf
	rm -rf ./libraries/SDL2_ttf-2.0.15
