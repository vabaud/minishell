NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

SRC = main.c \

OBJ = ${SRC:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${INCLUDE}

clean:
	${RM} ${OBJ} ${NAME}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
