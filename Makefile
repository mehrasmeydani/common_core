# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehras <mehras@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 17:28:13 by mehras            #+#    #+#              #
#    Updated: 2025/04/18 17:19:18 by mehras           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
			ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c\
			ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
			ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

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

so:
	$(GCC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY:		all clean fclean re