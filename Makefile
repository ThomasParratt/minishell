# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 10:22:54 by tparratt          #+#    #+#              #
#    Updated: 2024/06/11 10:56:48 by tparratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRC			=	minishell.c \
					validation.c \
					first_split.c \
					second_split.c \
					trim.c \
					parsing.c \
					expansion.c \
					paths.c \
					utils.c \
					execution.c \
					redirect.c \
					signals.c \
					heredoc.c \
					builtins/echo-pwd-env.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/unset.c \
					builtins/builtin_check.c \

LIBFT		=	libft/libft.a

OBJ			=	$(SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		=	-I /Users/$(USER)/.brew/opt/readline/include/readline.h -Wextra -Wall -Werror

LDFLAGS 	=	-L /Users/$(USER)/.brew/opt/readline/lib

$(NAME):	$(OBJ)
			make -C ./libft
			$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS) -lreadline

all:		$(NAME)

clean:
			make clean -C libft
			${RM} $(OBJ)

fclean: 	clean
			make fclean -C libft
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re