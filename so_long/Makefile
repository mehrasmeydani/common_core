# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/06/04 14:27:19 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c img.c map2.c map.c free.c mlx.c mlx2.c
SRCS		= ${addprefix ${PRE}, ${SRC}}
SRC_BONUS	= main_bonus.c img_bonus.c map2_bonus.c map_bonus.c free_bonus.c\
				mlx_bonus.c mlx2_bonus.c
SRCS_BONUS	= ${addprefix ${PRE_BONUS}, ${SRC_BONUS}}
PRE			= ./srcs/
PRE_BONUS	= ./srcs_bonus/
HEAD		= ./header/
NAME		= so_long
NAME_BONUS	= so_long_b
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= cd libft
OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}
RM			= rm -f
CC			= cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${OBJS} -I ${HEAD} -o ${NAME} ./libft/libft.a -lX11 -lm -lXext -lmlx 

${NAME_BONUS}:	${OBJS_BONUS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} ${OBJS_BONUS} -I ${HEAD} -o ${NAME_BONUS} ./libft/libft.a -lX11 -lm -lXext -lmlx 

bonus:		${NAME_BONUS}

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