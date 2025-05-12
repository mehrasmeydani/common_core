# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/05/12 21:00:04 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c 
SRCS		= ${addprefix ${PRE}, ${SRC}}
PRE			= ./srcs/
HEAD		= ./header/
NAME		= so_long
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
			cc ${CFLAGS} ${OBJS} -I ${HEAD} -o ${NAME} ./libft/libft.a -g -lmlx -lXext

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME}

re:			fclean all
			

.PHONY:		all clean fclean re