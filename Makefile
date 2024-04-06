# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 18:08:45 by s0nia             #+#    #+#              #
#    Updated: 2024/03/31 16:29:21 by s.veselova       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBFTDIR = libft/
READLINE = readline

GREEN = \e[1;92m
PINK = \e[1;95m
BLUE = \e[1;94m
DEFAULT = \033[0m

SRCS = src/main.c \
		src/cleanup_utils.c \
		src/execute.c \
		src/mini_utils.c \
		src/env_handler.c \
		src/export.c \
		src/ft_realloc.c

INCLUDE = -L ./libft -lft -Iincludes

OBJS = ${SRCS:.c=.o}


all: ${LIBFT} ${NAME}
	@echo "${GREEN}All tasks done *^‿^*"

${LIBFT}:
	@make --no-print-directory -C libft
	@make --no-print-directory -C libft bonus
	@echo "$(GREEN)Libft compiled * ^ ω ^"

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${SRCS} ${LIBFT}
	@echo "$(BLUE)Compiling minishell..${DEFAULT}"; sleep 2
	@${CC} ${FLAGS} ${LIBFT} ${SRCS} -lreadline -lncurses -o ${NAME} ${INCLUDE}
	@echo "${GREEN}minishell compiling done * ^ ω ^"


clean:
	@${RM} ${OBJS}
	@cd ${LIBFTDIR} && ${MAKE} --no-print-directory clean
	@echo "${GREEN}object files cleaning done *^‿^*"


fclean: clean
	@${RM} ${NAME}
	@make --no-print-directory -C libft fclean
	@echo "${GREEN}executables cleaning done *^‿^*"

re: fclean all

.PHONY: all clean fclean re