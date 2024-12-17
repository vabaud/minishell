# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 18:29:32 by vabaud            #+#    #+#              #
#    Updated: 2024/12/17 20:07:06 by vabaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

SRCS    		=	ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putstr_fd.c \
					ft_strchr.c \
					ft_strlen.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_strrchr.c \
					ft_memset.c \
					ft_memcpy.c \
					ft_bzero.c \
					ft_memmove.c \
					ft_strncmp.c \
					ft_strlcpy.c \
					ft_memchr.c \
					ft_strlcat.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_strdup.c \
					ft_calloc.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_split.c \
					ft_itoa.c \
					ft_strtrim.c \
					ft_putnbr_fd.c \
					ft_strmapi.c \
					ft_striteri.c \
					get_next_line.c \
					get_next_line_utils.c \
					ft_printf.c \
                    ft_putchar.c \
                    ft_putnbr.c \
                    ft_putstr.c \
                    ft_putunsignednbr.c \
                    ft_hexa.c \
					ft_strcharadd.c \
					ft_strcmp.c \
					ft_strjoin_and_free.c \

					

					
OBJS			=	$(SRCS:.c=.o)

BONUS			=	ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c \

BONUS_OBJS		= 	$(BONUS:.c=.o)

all: ${NAME}

${NAME}:		${OBJS} $(BONUS_OBJS)
				ar rcs $(NAME) ${OBJS}
clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
fclean:			clean
				$(RM) $(NAME)	
bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
re: fclean ${NAME}

.PHONY: all, clean, fclean, re	

.SILENT: