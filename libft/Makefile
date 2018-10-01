# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 09:16:22 by ndubouil          #+#    #+#              #
#    Updated: 2018/09/23 22:08:47 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
AR		=	/usr/bin/ar
RANLIB	=	/usr/bin/ranlib
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror

# Directories

H		=	./includes
P		=	./ft_printf
T		=	./trees

# Files

SRC		=	ft_putchar.c			\
	  	ft_putstr.c					\
	  	ft_putchar_fd.c				\
	  	ft_putstr_fd.c				\
	  	ft_ispositive.c				\
	  	ft_putnbr.c					\
	  	ft_putnbr_fd.c				\
	  	ft_putendl.c				\
	  	ft_putendl_fd.c				\
	 	ft_strclr.c					\
	  	ft_striter.c				\
	  	ft_striteri.c				\
	  	ft_strequ.c					\
	  	ft_strnequ.c				\
	  	ft_memalloc.c				\
	  	ft_memdel.c					\
	  	ft_strnew.c					\
	  	ft_strdel.c					\
	  	ft_strlen.c					\
	  	ft_isalpha.c				\
	  	ft_isupper.c				\
	  	ft_islower.c				\
	  	ft_toupper.c				\
	  	ft_tolower.c				\
	  	ft_isdigit.c				\
	  	ft_isalnum.c				\
	  	ft_isascii.c				\
	  	ft_isprint.c				\
	  	ft_strmap.c					\
	  	ft_strmapi.c				\
	  	ft_strsub.c					\
	  	ft_strjoin.c				\
	  	ft_strtrim.c				\
	  	ft_isspace_tab_nl.c			\
	  	ft_strdup.c					\
	  	ft_strcpy.c					\
	  	ft_wstrcpy.c				\
	  	ft_strncpy.c				\
	  	ft_strcat.c					\
	  	ft_strpos.c					\
	  	ft_strncat.c				\
	  	ft_strlcat.c				\
	  	ft_strchr.c					\
	  	ft_strrchr.c				\
	  	ft_strcmp.c					\
	  	ft_strncmp.c				\
	  	ft_strstr.c					\
	  	ft_strnstr.c				\
	  	ft_atoi.c					\
	  	ft_isspace.c				\
	  	ft_itoa.c					\
	  	ft_strrev.c					\
	  	ft_strsplit.c				\
	  	ft_memset.c					\
	  	ft_memcpy.c					\
	  	ft_memmove.c				\
	  	ft_memccpy.c				\
	  	ft_memchr.c					\
	  	ft_memcmp.c					\
	  	ft_bzero.c					\
	  	ft_strsplit.c				\
	  	ft_count_words.c			\
	  	ft_lstnew.c					\
	  	ft_lstdelone.c				\
	  	ft_lstdel.c					\
	  	ft_lstadd.c					\
	  	ft_lstiter.c				\
	  	ft_lstmap.c					\
	  	ft_isblank.c				\
	  	ft_str_is_alpha.c			\
	  	ft_str_is_lowercase.c		\
	  	ft_str_is_uppercase.c		\
	  	ft_iscntrl.c				\
	  	ft_isgraph.c				\
	  	ft_str_is_numeric.c			\
	  	ft_str_is_printable.c		\
	  	ft_lstaddend.c				\
	  	ft_lstlen.c					\
	  	ft_sqrt.c					\
	  	ft_lsti.c					\
	  	ft_lli_itoa_base.c			\
	  	ft_ulli_itoa_base.c			\
	  	get_next_line.c				\
		ft_itoa_base.c				\
		ft_count.c					\
		$(T)/ft_btree_apply_infix.c		\
		$(T)/ft_btree_apply_prefix.c		\
		$(T)/ft_btree_apply_rev_infix.c	\
		$(T)/ft_btree_apply_suffix.c		\
		$(T)/ft_btree_create_node.c		\
		$(T)/ft_btree_del.c				\
		$(T)/ft_btree_insert_data.c		\
		$(T)/ft_btree_level_count.c		\
		$(T)/ft_btree_nodes_count.c		\
		$(T)/ft_btree_search_item.c		\
		$(T)/left_rotation.c

OBJ		=	$(patsubst %.c,%.o,$(SRC))

HFILES	=	$(H)/libft.h			\
			$(H)/get_next_line.h	\
			$(H)/libftprintf.h		\
			$(H)/btree.h

# Name

NAME	=	libft.a

.PHONY: all clean fclean re

all:		$(NAME)
			@true

$(NAME):	$(OBJ) $(HFILES) $(P) Makefile
			@$(AR) rc $(NAME) $(OBJ)
			@$(RANLIB) $(NAME)
			@echo "Compiling ft_printf"
			@make -C $(P)
			@mv $(P)/libftprintf.a $(NAME)
			@echo "Building $(NAME)"
			@$(AR) rc $(NAME) $(OBJ)
			@$(RANLIB) $(NAME)
			@echo "The library $(NAME) is ready"

%.o:		%.c
			@echo "Creating $@ ..."
			@$(CC) $(CFLAGS) -c $< -o $@ -I$(H)

clean:
			@echo "Cleaning libft Objs ..."
			@$(RM) -f $(OBJ)
			@make clean -C $(P)

fclean: clean
			@echo "Cleaning $(NAME)"
			@$(RM) -f $(NAME)
			@make fclean -C $(P)

re: fclean all
