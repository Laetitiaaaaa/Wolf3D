# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llejeune <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 18:59:27 by llejeune          #+#    #+#              #
#    Updated: 2019/03/14 19:57:13 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = main.c 

INIT_SRC = init.c 

OBJ = $(SRC:.c=.o) \
	$(INIT_SRC:.c=.o)

SRC_PATH = ./src/

INIT_PATH = ./src/init/

OBJ_PATH = ./objs/

SOURCES = $(addprefix $(SRC_PATH), $(SRC)) \
		  $(addprefix $(INIT_PATH), $(INIT_SRC))

OBJETS = $(addprefix $(OBJ_PATH), $(OBJ))

FLAGS = -Wall -Wextra -Werror

INC = -I ./includes

LIBFT = ./libft/libft.a

LIBRARIES = -L ./libui -lSDL2 -lSDL2_image -framework OpenGL -framework AppKit \
            -L ./libft -lft 

all: $(NAME)

$(NAME): $(OBJETS)
	gcc $(FLAGS) $(INC) $(OBJETS) $(LIBRARIES) -o $(NAME)                                 #`sdl2-config --cflags --libs`

$(OBJ_PATH)%.o: $(SOURCES)%.c $(LIBFT) ./includes/wolf3d.h
	mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(FLAGS) $(INC) -o $@ -c $< 

$(LIBFT): FORCE
	make -C ./libft

FORCE:

clean:
	make fclean -C ./libft
	rm -rf $(OBJ_PATH) ; echo "Obj Cleaned"

fclean : clean
	rm -rf $(NAME) ; echo "Exec Cleaned"

re : fclean all

.PHONY : all clean fclean re
