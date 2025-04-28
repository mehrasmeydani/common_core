# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 11:37:35 by megardes          #+#    #+#              #
#    Updated: 2025/04/28 15:42:26 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= ft_printf.c
SRCS	= ${addprefix ${PRE}, ${SRC}}
OBJS	= ${SRCS:.c=.o}
PRE		= ./
HEAD	= ./
NAME	= libftprintf.a
LIBC	= ar rcs
LIBR	= ranlib
RM		= rm -f
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

all:			${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			(cd libft && make)
			cp libft/libft.a ${NAME}
			${LIBC} ${NAME} ${OBJS}
			${LIBR} ${NAME}


clean:
			(cd libft && make clean)
			rm -f ${OBJS}

fclean:		clean
			(cd libft && make fclean)
			rm -f ${NAME}
			rm -f a.out
			

re:			fclean all

.PHONY:		all clean fclean re