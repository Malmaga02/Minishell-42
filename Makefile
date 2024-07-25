NAME = minishell

CC = cc
INCLUDES = ./includes
CFLAGS = -Wextra -Werror -Wall -g -I$(INCLUDES)
COMPILE = $(CC) $(CFLAGS) -c
RM = rm -f


LIBFT_DIR = ./libft.plus

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RESET=\033[0m

SRC =	./main.c \
		./src/builtins/echo.c \
		./src/builtins/env.c \
		./src/builtins/exit.c \
		./src/builtins/export.c \
		./src/builtins/export_utils.c \
		./src/builtins/pwd.c \
		./src/builtins/unset.c \
		./src/builtins/cd.c \
		./src/free_exit_handling/free_parsing.c \
		./src/lst_input_handling/dll_input_addback.c \
		./src/lst_input_handling/dll_input_addfront.c \
		./src/lst_input_handling/dll_input_clear.c \
		./src/lst_input_handling/dll_input_last.c \
		./src/lst_input_handling/dll_input_new.c \
		./src/lst_input_handling/dll_input_size.c \
		./src/parsing/expansion/expand_with_quotes.c \
		./src/parsing/expansion/expand.c \
		./src/parsing/expansion/get_env.c \
		./src/parsing/expansion/handling_env.c \
		./src/parsing/get_info/get_all_info.c \
		./src/parsing/get_info/get_args_mtx.c \
		./src/parsing/get_info/get_arr_token.c \
		./src/parsing/get_info/get_input_complete.c \
		./src/parsing/get_info/get_merge_flags.c \
		./src/parsing/get_info/get_merged_line.c \
		./src/parsing/get_info/get_mtx_input.c \
		./src/parsing/get_info/get_void_cmd.c \
		./src/parsing/handlers/handling_args_mtx.c \
		./src/parsing/handlers/handling_char.c \
		./src/parsing/handlers/handling_merge_flag.c \
		./src/parsing/handlers/handling_merged_line.c \
		./src/parsing/handlers/handling_mtx_and_lists.c \
		./src/parsing/handlers/handling_quotes_as_word_token.c \
		./src/parsing/handlers/handling_token.c \
		./src/parsing/handlers/trim_quotes.c \
		./src/executor/exec_main.c \
		./src/executor/exec_utils.c \
		./src/executor/exec_free.c \
        ./src/executor/envp_utils.c \
		./src/executor/general_utils.c \
		./src/executor/redirect.c \
		./src/executor/redirect_utils.c \
		./src/executor/heredoc.c \
		./src/executor/signal.c \
		./src/executor/heredoc_utils.c \
		./src/executor/handle_child.c

all: $(NAME)

$(NAME): $(SRC)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -I. -I$(INCLUDES) $(SRC) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "$(BLUE)	MINISHELL COMPILED!$(RESET)"


valgrind: $(NAME)
	valgrind --quiet --leak-check=full --track-fds=yes -s --show-reachable=yes --suppressions=readline.supp ./$(NAME)

clean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all
.SILENT: