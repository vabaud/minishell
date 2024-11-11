NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFTDIR = libft/

SRC = main.c \
		syntax_checker.c \

OBJ = ${SRC:.c=.o}

INCLUDE = libft/libft.a

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${LDFLAGS} ${INCLUDE}

clean:
	${RM} ${OBJ} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
