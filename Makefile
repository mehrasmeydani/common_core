# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehras <mehras@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 17:28:13 by mehras            #+#    #+#              #
#    Updated: 2025/04/16 17:29:00 by mehras           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= 

SRC_B		= 

SRCS		= ${addprefix ${PRE}, ${SRC}}
SRCS_B		= ${addprefix ${PRE}, ${SRC_B}}
OBJS		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}
PRE			= ./
HEAD		= ./
NAME		= libft.a
LIBC		= ar rc
LIBR		= ranlib
RM			= rm -f
GCC			= cc
CFLAGS		= -Wall -Wextra -Werror

all:			${NAME}

.c.o:
			${GCC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${LIBC} ${NAME} ${OBJS}
			${LIBR} ${NAME}


clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f ${OBJS_B}
			rm -f libft.so
			rm -f a.out

re:			fclean all

bonus:			${OBJS} $(OBJS_B)
				ar rcs $(NAME) $(OBJS) $(OBJS_B)

.PHONY:		all clean fclean re