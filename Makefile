# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llejeune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/18 19:20:02 by llejeune          #+#    #+#              #
#    Updated: 2019/03/19 16:10:55 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d


INC_DIR = $(shell find includes -type d) $(shell find libft -type d) $(shell find ~/.brew/include/SDL2 -type d)

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = obj

SRC = loop.c \
	  main.c \
	  init.c \
	  map.c \
	  convert.c \
	  dda.c \
	  dda_horizontalwall.c \
	  init_event.c \
	  draw_2d.c \
	  draw_background.c \
	  menu.c \
	  draw_3d.c \
	  quit.c \


OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

LIBS = SDL2 SDL2_image ft

LIB_DIR = ./libft \
		  ~/.brew/lib \
		  ./libraries/SDL2_image \

FRAMEWORK = OpenGL AppKit

CC = gcc
#-g -ggdb

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

IFLAG = $(foreach dir, $(INC_DIR), -I$(dir) ) -I libraries/dist/include -I /usr/local/Cellar/sdl2/2.0.9/include/SDL2

CFLAG = -Wall -Wextra -Werror

LFLAG = $(foreach dir, $(LIB_DIR), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) ) \
#  -L /usr/local/Cellar/sdl2/2.0.9/lib \
  -L libraries/dist/lib

HEADER = includes/wolf3d.h

LIBFTA = ./libft/

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG)

$(OBJ_DIR)/%.o: %.c $(HEADER) $(LIBFTA)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)

$(LIBFTA): FORCE
	make -C libft

FORCE:

clean:
	make clean -C libft
	@echo "Cleaning the project ... \c"
	rm -rf $(OBJ_DIR)
	@echo "DONE"

fclean: clean
	@echo "Fcleaning the project ... \c"
	rm $(NAME)
	@echo "DONE"

re: fclean
	@echo "Restarting the compilation"
	make $(NAME)

relib:
	make re -C libft

image: libraries/dist/lib/libSDL2_image.dylib

libraries/dist/lib/libSDL2_image.dylib: libraries/dist/lib/libSDL2_ttf.dylib
	mkdir -p libraries
	tar -xzf filetar/SDL2_image-2.0.4.tar.gz -C libraries
	cd libraries/SDL2_image-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries/dist
	make -C ./libraries/SDL2_image-2.0.4
	make -C ./libraries/SDL2_image-2.0.4 install
# 	mv ./libraries/SDL2_image-2.0.4/include/SDL2/SDL_image.h ./includes
# 	mv ./libraries/SDL2_image-2.0.4/lib/ ./libraries/SDL2_image
# 	rm -rf ./libraries/SDL2_image-2.0.4


libraries/dist/lib/libfreetype.dylib:
	mkdir -p libraries
	tar -xzf ./filetar/freetype-2.4.11.tar.gz -C libraries
	cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries/dist
	make -C ./libraries/freetype-2.4.11
	make -C ./libraries/freetype-2.4.11 install


libraries/dist/lib/libSDL2_ttf.dylib: libraries/dist/lib/libfreetype.dylib
	mkdir -p libraries
	tar -xzf ./filetar/SDL2_ttf-2.0.15.tar.gz -C libraries
	cd libraries/SDL2_ttf-2.0.15 ; FT2_CONFIG=$(shell pwd)/libraries/dist/bin/freetype-config ./configure --prefix=$(shell pwd)/libraries/dist
	make -C ./libraries/SDL2_ttf-2.0.15
	make -C ./libraries/SDL2_ttf-2.0.15 install
# 	mv ./libraries/SDL2_ttf-2.0.15/include/SDL2/SDL_ttf.h ./includes/
# 	mv ./libraries/SDL2_ttf-2.0.15/lib ./libraries/SDL2_ttf
# 	rm -rf ./libraries/SDL2_ttf-2.0.15
