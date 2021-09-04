# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 18:49:13 by rkhelif           #+#    #+#              #
#    Updated: 2021/09/04 07:19:52 by rkhelif          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = pipex
RM = rm -rf
DIR_OBJ = other
DIR_SRC = src
DIR_INC = inc

SRCS = pipex.c \
		error1.c \
		utilities1.c \
		utilities2.c \
		free.c \
		process.c \
		process2.c \
		ft_split.c

OBJS = ${addprefix ${DIR_OBJ}/,${SRCS:.c=.o}}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	${CC} $(CFLAGS) -I ${DIR_INC} -c $< -o $@

clean:
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re: fclean all
