# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/05/18 18:16:22 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c 
SRCS		= ${addprefix ${PRE}, ${SRC}}
PRE			= ./srcs/
HEAD		= ./header/
NAME		= pipex
NAME_TEST	= test
TEST_S		= test.c
TEST_O		= ${TEST_S:.c=.o}
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= cd libft
OBJS		= ${SRCS:.c=.o}
RM			= rm -f
CC			= cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${OBJS} -I ${HEAD} -o ${NAME} ./libft/libft.a

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS} ${TEST_O}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME} ${NAME_TEST}

test:		${TEST_O}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${TEST_O} -I ${HEAD} -o ${NAME_TEST} ./libft/libft.a

re:			fclean all
			

.PHONY:		all clean fclean re