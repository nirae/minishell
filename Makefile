# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 19:48:44 by ndubouil          #+#    #+#              #
#    Updated: 2019/01/24 05:20:44 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=address

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)includes/
H		=	./includes/
SRC		=	./src/
P		=	$(SRC)parsing/
ENV		=	$(SRC)environment/
BT		=	$(SRC)builtins/
CD		=	$(BT)cd/
ENVBT	=	$(BT)env/

#  Files

HFILES	=	$(H)minishell.h
MAIN	=	$(SRC)main.c
SRCS	=	$(MAIN)															\
			$(P)read_prompt.c												\
			$(P)get_complete_command.c										\
			$(P)replace_dollar.c											\
			$(SRC)get_path_of_bin.c											\
			$(SRC)ft_strtabdel.c											\
			$(SRC)exec_command.c											\
			$(P)minishell_parser.c											\
			$(ENV)get_env_var_by_name.c										\
			$(ENV)env_lst_to_tab.c											\
			$(ENV)env_tab_to_lst.c											\
			$(ENV)change_env_var.c											\
			$(ENV)remove_env_var.c											\
			$(ENV)add_env_var.c												\
			$(ENV)create_varenv.c											\
			$(ENV)del_env_var.c												\
			$(P)ft_strsplit_whitespace.c									\
			$(SRC)error.c													\
			$(BT)exit_builtin.c												\
			$(BT)setenv_builtin.c											\
			$(BT)unsetenv_builtin.c											\
			$(BT)echo_builtin.c												\
			$(ENVBT)env_builtin.c											\
			$(ENVBT)ft_lstcpy.c												\
			$(ENVBT)manage_envvar_args.c									\
			$(BT)options.c													\
			$(BT)manage_builtins.c											\
			$(CD)get_final_path.c											\
			$(CD)get_pwd_for_cd.c											\
			$(CD)check_path_errors.c										\
			$(CD)ft_stringtab_len.c											\
			$(CD)ft_strjointab.c											\
			$(CD)ft_realloc_addend_tab.c									\
			$(CD)build_pwd_tab.c											\
			$(CD)cd_builtin.c

OBJ		=	$(patsubst %.c,%.o,$(SRCS))

# Name of the project

NAME	=	minishell

.PHONY: all clean fclean re

# Rules

all:		$(NAME)
		@true

$(NAME):	Makefile $(OBJ) $(MAIN) $(HFILES) $(LIBFT)
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building $(NAME) ..."
		@$(CC) $(CFLAGS) $(OBJ) -I$(H) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
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
