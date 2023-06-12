# NAME	= minishell

# LIBFT	= ./libft/libft.a
# SRCS	= ./execution/minishell.c ./execution/builtins.c ./execution/redirections.c \
# 		./execution/heredoc.c ./execution/env_utils.c ./execution/envp_utils.c \
# 		./execution/utils.c ./parsing/utils.c ./parsing/parsing.c ./parsing/utils.c \
# 		./parsing/new_beginning.c ./parsing/expanding.c ./parsing/fill_the_node.c \
# 		./parsing/syntaxe_error.c ./execution/pipes.c ./execution/signals.c
# OBJS	= ${SRCS:.c=.o}

# CC		= cc
# CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address

# RM		= rm -f

# %.o : %.c
# 	${CC} ${CFLAGS} -c $^ -o $@

# all:	${NAME}

# ${LIBFT}:
# 	@make -C ./libft

# ${NAME}:	${OBJS} ${LIBFT}
# 	$(CC) $(CFLAGS) $^ -lreadline -o $@
# 	@make clean -C ./libft

# clean:
# 	$(RM) ${OBJS}

# fclean:	clean
# 	@make fclean -C ./libft
# 	$(RM) ${NAME}

# re:	fclean $(NAME)

# my:	re
# 	clear
# 	@rm -rf ${OBJS}

# .PHONY: all clean fclean re

NAME	= minishell

LIBFT	= ./libft/libft.a
SRCS	= ./execution/minishell.c ./execution/builtins.c ./execution/redirections.c \
		./execution/heredoc.c ./execution/env_utils.c ./execution/envp_utils.c \
		./execution/utils.c ./parsing/utils.c ./parsing/parsing.c ./parsing/utils.c \
		./parsing/new_beginning.c ./parsing/expanding.c ./parsing/fill_the_node.c \
		./parsing/syntaxe_error.c ./execution/pipes.c ./execution/signals.c
OBJS	= ${SRCS:.c=.o}

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
NRLFLAGS = -lreadline -g -fsanitize=address

RM		= rm -f

%.o : %.c
	${CC} ${CFLAGS} -c $^ -o $@

all:	${NAME}

${LIBFT}:
	@make -C ./libft

${NAME}:	${OBJS} ${LIBFT}
	$(CC) $(CFLAGS) $(NRLFLAGS) $^ -o $@
	@make clean -C ./libft

clean:
	$(RM) ${OBJS}

fclean:	clean
	@make fclean -C ./libft
	$(RM) ${NAME}

re:	fclean $(NAME)

my:	re
	clear
	@rm -rf ${OBJS}

.PHONY: all clean fclean re

