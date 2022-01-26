NAME		= pagerank

SRCS		= srcs/main.c srcs/list_utils.c srcs/parse_file.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I.

all:		${NAME}

$(NAME):	${OBJS}
			gcc ${CFLAGS} -o ${NAME} ${OBJS}

.c.o:
			gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re