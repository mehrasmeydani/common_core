# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/05/26 13:11:03 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S			= server
SRC_S			= main.c 
SRCS_S			= ${addprefix ${PRE_S}, ${SRC_S}}
PRE_S			= ./srcs_server/
OBJS_S			= ${SRCS_S:.c=.o}
NAME_C			= client
SRC_C			= main.c 
SRCS_C			= ${addprefix ${PRE_C}, ${SRC_C}}
PRE_C			= ./srcs_client/
OBJS_C			= ${SRCS_C:.c=.o}
HEAD			= ./header/
NAME_TEST		= test
TEST_S			= test.c
TEST_O			= ${TEST_S:.c=.o}
CFLAGS			= -Wall -Wextra -Werror
LIBFT			= cd libft
RM				= rm -f
CC				= cc
MAKEFLAGS		+= --no-print-directory

all:		${NAME_C} ${NAME_S}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME_C}:	${OBJS_C}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${OBJS_C} -I ${HEAD} -o ${NAME_C} ./libft/libft.a

${NAME_S}:	${OBJS_S}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${OBJS_S} -I ${HEAD} -o ${NAME_S} ./libft/libft.a

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS_C} ${OBJS_S} ${TEST_O}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME_S} ${NAME_C} ${NAME_TEST}

test:		${TEST_O}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${TEST_O} -I ${HEAD} -o ${NAME_TEST} ./libft/libft.a -g

re:			fclean all
			

.PHONY:		all clean fclean re