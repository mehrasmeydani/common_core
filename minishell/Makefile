# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 18:57:46 by megardes          #+#    #+#              #
#    Updated: 2025/06/18 20:19:01 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c
SRCS		= ${addprefix ${PRE}, ${SRC}}
PRE			= ./srcs/
HEAD		= ./header/
NAME		= minishell
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
			${CC} ${CFLAGS} ${OBJS} -I ${HEAD} -o ${NAME} ./libft/libft.a -lreadline

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS}
			${RM} ${OBJS_BONUS}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME}
			${RM} ${NAME_BONUS}

re:			fclean all
			

.PHONY:		all clean fclean re