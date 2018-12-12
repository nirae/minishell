# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 19:48:44 by ndubouil          #+#    #+#              #
#    Updated: 2018/12/12 18:45:18 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)includes/
H		=	./includes/
SRC		=	./src/
P		=	$(SRC)parsing/
ENV		=	$(SRC)environment/
BT		=	$(SRC)builtins/

#  Files

HFILES	=	$(H)minishell.h
MAIN	=	$(SRC)main.c
SRCS	=	$(SRC)read_prompt.c												\
			$(SRC)get_complete_command.c									\
			$(SRC)minishell_split.c											\
			$(P)minishell_parser.c											\
			$(ENV)get_env_var_by_name.c										\
			$(ENV)change_env_var.c											\
			$(ENV)del_env_var.c												\
			$(SRC)ft_split_escape.c											\
			$(BT)exit_builtin.c												\
			$(BT)cd_builtin.c

OBJ		=	$(patsubst %.c,%.o,$(SRCS))
# Name

NAME	=	minishell

.PHONY: all clean fclean re

all:		$(NAME)
		@true

$(NAME):	$(OBJ) $(MAIN) $(HFILES) $(LIBFT) Makefile
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building $(NAME) ..."
		@$(CC) $(CFLAGS) $(MAIN) $(OBJ) -I$(H) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
		@echo "I'm READY"

%.o: 		%.c
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -I$(H) -I$(ILIBFT) -c $< -o $@

clean:
		@echo "Cleaning Objs ..."
		@$(RM) -f $(OBJ)
		@echo "Cleaning Libft Objs ..."
		@make clean -C $(LIBFT)

fclean:		clean
		@echo "Cleaning $(NAME) exec"
		@$(RM) -f $(NAME)
		@echo "Cleaning libft exec"
		@make fclean -C $(LIBFT)

re:			fclean all
