# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 08:41:35 by ndubouil          #+#    #+#              #
#    Updated: 2018/07/08 01:24:18 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
AR		=	/usr/bin/ar
RANLIB	=	/usr/bin/ranlib
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror

# Directories

LIB		=	..
H		=	../includes
PA		=	./parser
PR		=	./printer
U_TOOLS	=	./printer/unicode_tools
B		=	./buffer

#  Files

HFILES	=	$(H)/libftprintf.h
SRC		=	$(PA)/parser.c					\
			$(PA)/is_valid_flags.c			\
			$(PA)/is_valid_sizeflag.c		\
			$(PA)/is_valid_type.c			\
			$(PA)/init_flags.c				\
			$(PA)/set_flags.c				\
			$(PA)/set_size.c				\
			$(PA)/set_type.c				\
			$(PA)/set_width.c				\
			$(PA)/set_precision.c			\
			$(PR)/printer.c					\
			$(PR)/print_char.c				\
			$(PR)/print_big_char.c			\
			$(PR)/print_big_string.c		\
			$(PR)/print_string.c			\
			$(PR)/print_address.c			\
			$(PR)/print_percent.c			\
			$(PR)/print_number.c			\
			$(PR)/print_octal.c				\
			$(PR)/print_hexa.c				\
			$(PR)/hexa_tools.c				\
			$(PR)/print_unsigned_number.c	\
			$(B)/buffer.c					\
			$(U_TOOLS)/get_big_char.c		\
			$(U_TOOLS)/ft_bigcharlen.c		\
			$(U_TOOLS)/ft_bigstrlen.c		\
			$(U_TOOLS)/ft_wstrlen.c			\
			ft_printf.c

OBJ		=	$(patsubst %.c,%.o,$(SRC))

# Name

NAME	=	libftprintf.a

.PHONY: all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJ) $(HFILES) $(LIB) Makefile
		@echo "Building $(NAME) ..."
		@cp $(LIB)/libft.a $(NAME)
		@$(AR) r $(NAME) $(OBJ)
		@$(RANLIB) $(NAME)
		@echo "$(NAME) Ready"

%.o: 		%.c
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -c $< -o $@ -I$(H)

clean:
		@$(RM) -f $(OBJ)

fclean:		clean
		@$(RM) -f $(NAME)

re:			fclean all
