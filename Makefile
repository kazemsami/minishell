NAME = minishell
SRC = minishell.c exec.c sig.c env.c parse.c token.c builtin.c \
		echo_cmd.c get_env.c pwd.c type.c pipe.c pipe2.c utils.c \
		exit.c env1.c cd.c unset.c export.c export_utils.c fix_token.c extra.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ./libft/libft.a ${SRC}
	${CC} ${CFLAGS} ${SRC} -Ilibft ./libft/libft.a -lreadline  -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -o $@

./libft/libft.a:
	@make -C ./libft

clean:
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	rm -rf ${NAME}

re: fclean all