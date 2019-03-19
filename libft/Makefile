# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleblond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/21 20:32:08 by jleblond          #+#    #+#              #
#    Updated: 2019/03/18 19:49:12 by llejeune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = $(shell find includes -type d)

SRC_DIR = $(shell find srcs -type d)

OBJ_DIR = obj

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c \
ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstcpy.c \
ft_word_nbr_counter.c ft_lstlen.c ft_islower.c ft_isupper.c \
get_next_line.c ft_aatoii.c ft_color_val_calculate.c ft_float_abs.c  \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

CC = gcc

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

IFLAG = $(foreach dir, $(INC_DIR), -I$(dir) )

CFLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Creating $@ ... \c"
	@ar rcs $(NAME) $(OBJ)
	@echo "DONE"

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@echo "Compiling $<... \c"
	@$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)
	@echo "DONE"

clean:
	@echo "Cleaning libft ... \c"
	@rm -f $(OBJ)
	@echo "DONE"

fclean: clean
	@echo "Fcleaning libft ... \c"
	@rm -f $(NAME)
	@echo "DONE"

re:
	@make fclean
	@echo "Restarting the compilation !"
	@make all

.PHONY: all clean fclean re
