# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/04/28 19:06:38 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c
SRC_B	=
SRCS	= ${addprefix ${PRE}, ${SRC}}
SRCS_B	= ${addprefix ${PRE}, ${SRC_B}}
PRE		= ./srcs/
HEAD	= ./header/
NAME	= push_swap
CFLAGS	= -Wall -Wextra -Werror
LIBFT	= cd libft
OBJS	= ${SRCS:.c=.o}
RM		= rm -f
CC		= cc

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@${LIBFT} && make all
			cc ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME} ./libft/libft.a

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS}

fclean: 	clean
			@${LIBFT} && make fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re