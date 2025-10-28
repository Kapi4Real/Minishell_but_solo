#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// Pour tokenizer
typedef enum e_token_state
{
	OUTSIDE,
	IN_DOUBLE_QUOTES,
	IN_SINGLE_QUOTES
}	t_token_state;

typedef struct s_tokenizer
{
	char			*input;
	char			*buffer;
	char			**tab;
	t_token_state	state;
	int				pos_input;
	int				pos_buffer;
	int				pos_tab;
}	t_tokenizer;

// Structures de base
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				pipe[2];
	struct s_cmd	*next;
}	t_cmd;

// Parsing
t_token	*tokenize(char *input);
t_cmd	*parse(t_token *tokens);

char	**tokenizer(char *input);

// Execution
int		execute(t_cmd *commands);
int		exec_builtins(char **args);
int		is_builtin(char **args);

// Builtins
int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(void);
/*
int		ft_export(char **args);
int		ft_unset(char **args);
int		ft_env(void);
*/
int		ft_exit(char **args);

// Utils
void	free_commands(t_cmd *commands);
void	handle_error(char *msg);

#endif
