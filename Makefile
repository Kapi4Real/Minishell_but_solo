NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I.
RM = rm -f

SRC = src/main.c src/parsing/split_command.c src/exec/exec_builtins.c builtins/builts.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
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
