NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I. -Iincludes
RM = rm -f

SRC = src/main.c \
      src/shell_utils.c \
      src/signals.c \
      src/parsing/split_command_tokenizer.c \
      src/parsing/create_token.c \
      src/parsing/split_command_utils2.c \
      src/parsing/split_command_utils3.c \
      src/parsing/expand_variables.c \
      src/parsing/take_var_name.c \
      src/parsing/expand_variables_utils1.c \
      src/parsing/expand_variables_utils2.c \
      src/parsing/expand_buffer.c \
      src/exec/exec_builtins.c \
      src/exec/manage_pipe_utils.c \
      builtins/ft_echo.c \
      builtins/ft_cd.c \
      builtins/ft_pwd.c \
      builtins/ft_env.c \
      builtins/ft_exit.c \
      builtins/ft_export.c \
      builtins/ft_unset.c \
      src/exec/init_env.c \
      src/exec/env_utils.c \
      src/parsing/init_cmd.c \
      src/parsing/remove_quotes.c \
      src/parsing/add_arg_cmd.c \
      src/parsing/free_cmd.c \
      src/exec/get_cmd_path.c \
      src/exec/get_env.c \
      src/exec/execute_external.c \
      src/parsing/parser_main.c \
      src/parsing/parser_redirections.c \
      src/exec/manage_redirection.c \
      src/exec/manage_pipe.c \
        src/parsing/parser_main_utils.c \
    	src/parsing/heredoc.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) src/parsing/*.o src/exec/*.o builtins/*.o src/*.o
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
