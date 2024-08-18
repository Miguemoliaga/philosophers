# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartine <mmartine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 17:34:06 by mmartine          #+#    #+#              #
#    Updated: 2024/08/18 17:42:47 by mmartine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address # -fsanitize=thread

SRCS	=	main.c \
			mutex_act.c \
			routine.c \
			utils.c \
			utils_extra.c


INCLUDE	= -L${LIBFT} -lft 

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf


all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

clean:
		@${RM} ${OBJS} *.dSYM

fclean:		clean
		@${RM} ${NAME}

re:		fclean all

.PHONY:	clean re fclean bonus all