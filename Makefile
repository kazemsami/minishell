NAME = minishell
SRC = ./src/main/minishell.c ./src/exec/exec.c ./src/exec/pipe.c ./src/exec/pipe2.c \
		./src/signals/sig.c ./src/env/env.c ./src/env/env1.c ./src/env/get_env.c \
		./src/parsing/parse.c ./src/parsing/token.c ./src/parsing/fix_token.c ./src/parsing/type.c \
		./src/builtins/builtin.c ./src/builtins/export_utils.c \
		./src/builtins/echo_cmd.c  ./src/builtins/pwd.c ./src/builtins/export.c  \
		./src/builtins/exit.c ./src/builtins/cd.c ./src/builtins/unset.c \
		./src/utils/extra.c ./src/utils/utils.c
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