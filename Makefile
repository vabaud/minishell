NAME = minishell
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFTDIR = include/libft/

SRC = src/main.c \
		src/utils.c \
		src/parsing/syntax_checker.c \
		src/parsing/tokenization.c \
		src/parsing/tokenization_utils.c \
		src/parsing/parsing.c \
		src/parsing/parsing_utils.c \
		src/parsing/redirections.c \
		src/builtins/ft_pwd.c \
		src/env_utils.c \
		src/parsing/heredoc.c \
		src/signals.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_env.c \
		src/builtins/ft_unset.c \

OBJ = ${SRC:.c=.o}

INCLUDE = include/libft/libft.a

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
