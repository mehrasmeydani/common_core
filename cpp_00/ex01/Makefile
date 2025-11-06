# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megardes <megardes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 14:44:18 by codespace         #+#    #+#              #
#    Updated: 2025/11/06 22:33:00 by megardes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.cpp Contact.cpp PhoneBook.cpp
SRCS		= ${addprefix ${PRE_SRC}, ${SRC}}
PRE_SRC		= srcs/
HEAD		= header/
NAME		= phonebook
CFLAGS		= -Wall -Wextra -Werror -std=c++98
OBJ			= ${SRC:.cpp=.o}
PRE_OBJ		= obj/
OBJS		= ${addprefix ${PRE_OBJ}, ${OBJ}}
RM			= rm -fr
CC			= c++
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

$(PRE_OBJ)%.o:$(PRE_SRC)%.cpp
			mkdir -p $(PRE_OBJ)
			${CC} ${CFLAGS} -I ${HEAD} -o $@ -c $< 

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -I ${HEAD} ${SRCS} -o ${NAME}

clean: 
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME} $(PRE_OBJ)

re:			fclean all
			

.PHONY:		all clean fclean re