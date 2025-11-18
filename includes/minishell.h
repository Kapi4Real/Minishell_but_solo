#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

t_token	*tokenize(char *input);
t_cmd	*parse(t_token *tokens);
char	*remove_quotes(char *token);
t_cmd	*init_cmd(void);
void	add_arg_cmd(t_cmd *cmd, char *arg);
void	free_cmd(t_cmd *cmd);

char	**tokenizer(char *input);

int		execute(t_cmd *commands);
int		exec_builtins(char **args, t_env *env);
int		is_builtin(char **args);
int		execute_external(char **args, t_env *env);
int		execute_pipeline(t_cmd *cmd, t_env **env);
t_cmd	*parse_tokens(char **tokens);

void	execute_redirections(t_cmd *cmd);
int		apply_redirections(t_cmd *cmd, int *saved_stdin, int *saved_stdout);
void	restore_redirections_parent(int saved_stdin, int saved_stdout);
void	close_all_pipes(t_cmd *cmd);
void	setup_pipe(t_cmd *current, int prev_pipe_read);
int		create_pipe(t_cmd *current);
void	execute_child_process(t_cmd *current, t_env *env, int prev_pipe_read);

int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_exit(char **args, t_env *env);

t_env	*init_env(char **envp);
t_env	*ft_envnew(char *key, char *value);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_env(t_env *env);
void	ft_envclear(t_env **env);
char	*get_env(t_env *env, char *key);
char	*get_cmd_path(char *cmd, t_env *env);

void	free_commands(t_cmd *commands);
void	handle_error(char *msg);
void	free_args(char **args);

#endif
