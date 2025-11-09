# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/11/09 15:39:44 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c ft_bzero.c ft_calloc.c ft_isdigit.c ft_puts.c ft_atoi.c\
				check_in.c free_all.c locking.c thinker_print.c my_time.c\
				my_usleep.c starts.c routines.c forks.c check_meals.c threads.c monitoring.c
SRCS		=	${addprefix ${PRE_SRC}, ${SRC}}
PRE_SRC		=	srcs/
HEAD		=	header/
NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror
OBJ			=	${SRC:.c=.o}
PRE_OBJ		=	obj/
OBJS		=	${addprefix ${PRE_OBJ}, ${OBJ}}
RM			=	rm -fr
CC			= 	cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

$(PRE_OBJ)%.o:$(PRE_SRC)%.c
			mkdir -p $(PRE_OBJ)
			${CC} ${CFLAGS} -I ${HEAD} -o $@ -c $< 

${NAME}:	${OBJS}
			cc ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME}

clean: 
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME} $(PRE_OBJ)

re:			fclean all
			

.PHONY:		all clean fclean re