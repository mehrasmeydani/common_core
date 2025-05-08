# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/05/08 06:10:24 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c init.c ft_splits.c frees.c lis.c stack.c stack2.c ft_atol.c\
			ft_sort_long_tab.c check.c ft_nums.c ops.c direction.c opt.c ops2.c\
			max_min.c push_b.c push_swap.c 
B			= bonus
SRCS		= ${addprefix ${PRE}, ${SRC}}
SRC_B		= ${addprefix ${B}, ${SUF}}
SUF			= _bonus.c
SRCS_B		= ${addprefix ${PRE}, ${SRC_B}}
PRE			= ./srcs/
PRE_B		= ./srcs_bonus/
HEAD		= ./header/
NAME		= push_swap
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= cd libft
OBJS		= ${SRCS:.c=.o}
OBJS_B		= ${SRCS_B:.c=.o}
RM			= rm -f
CC			= cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

.c.o:
			@${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME} ./libft/libft.a

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS} ${OBJS_B}
			

.PHONY:		all clean fclean re