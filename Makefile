# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 19:48:44 by ndubouil          #+#    #+#              #
#    Updated: 2018/12/18 02:29:02 by ndubouil         ###   ########.fr        #
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
CD		=	$(BT)cd/

#  Files

HFILES	=	$(H)minishell.h
MAIN	=	$(SRC)main.c
SRCS	=	$(SRC)read_prompt.c												\
			$(SRC)get_complete_command.c									\
			$(SRC)minishell_split.c											\
			$(SRC)ft_strtabdel.c											\
			$(SRC)ft_arraylen.c											\
			$(SRC)exec_command.c											\
			$(P)minishell_parser.c											\
			$(ENV)get_env_var_by_name.c										\
			$(ENV)env_lst_to_tab.c										\
			$(ENV)change_env_var.c											\
			$(ENV)add_env_var.c												\
			$(ENV)create_varenv.c											\
			$(ENV)del_env_var.c												\
			$(SRC)ft_split_escape.c											\
			$(SRC)error.c													\
			$(BT)exit_builtin.c												\
			$(BT)echo_builtin.c												\
			$(BT)env_builtin.c												\
			$(BT)options.c												\
			$(CD)get_final_path.c												\
			$(CD)check_path_errors.c												\
			$(CD)ft_stringtab_len.c												\
			$(CD)ft_strjointab.c												\
			$(CD)ft_realloc_addend_tab.c												\
			$(CD)build_pwd_tab.c												\
			$(CD)cd_builtin.c

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
