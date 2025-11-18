NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I. -Iincludes
RM = rm -f

SRC = src/main.c \
      src/parsing/split_command.c \
      src/exec/exec_builtins.c \
      builtins/builts.c \
      src/exec/init_env.c \
      src/parsing/init_cmd.c \
      src/parsing/remove_quotes.c \
      src/parsing/add_arg_cmd.c \
      src/parsing/free_cmd.c \
      src/exec/get_cmd_path.c \
      src/exec/get_env.c \
      src/exec/execute_external.c \
      src/parsing/parser.c \
      src/exec/manage_pipe.c\
      src/exec/manage_pipe2.c\


OBJ = $(SRC:.c=.o)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "✅ Minishell compiled!"

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
