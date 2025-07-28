# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/07/28 18:49:19 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c not_bzero.c not_calloc.c
SRCS		= ${addprefix ${PRE}, ${SRC}}
PRE			= ./srcs/
HEAD		= ./header/
NAME		= philo
CFLAGS		= -Wall -Wextra -Werror
OBJS		= ${SRCS:.c=.o}
RM			= rm -f
CC			= cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

.c.o:
			@${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			cc ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME} -g

clean: 
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all
			

.PHONY:		all clean fclean re