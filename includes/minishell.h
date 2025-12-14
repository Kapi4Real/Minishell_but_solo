/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/wait.h>

void	create_file_redir(char **tokens, int i);

typedef struct s_env
{
	char			*name;
	char			*value;
	int				last_exit_status;
	struct s_env	*next;
}	t_env;

typedef enum e_token_state
{
	OUTSIDE,
	IN_DOUBLE_QUOTES,
	IN_SINGLE_QUOTES
}	t_token_mode;

typedef struct s_tokenizer
{
	char			*input;
	char			*buffer;
	char			**tab;
	t_token_mode	mode;
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
	int				heredoc_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_expand_data
{
	char	*result;
	size_t	*i;
	size_t	*j;
	size_t	*size;
	t_env	*env;
}	t_expand_data;

int		skip_command(char *command);
int		heredoc_redir(t_cmd *cmd, char **tokens, int i);
t_cmd	*parse(t_token *tokens);
char	*remove_quotes(char *token);
t_cmd	*init_cmd(void);
void	add_arg_cmd(t_cmd *cmd, char *arg);
void	free_cmd(t_cmd *cmd);

char	**tokenizer(char *input, t_env *env);
void	expand_tokens(char **tokens, t_env *env);

int		execute(t_cmd *commands);
int		exec_builtins(char **args, t_env **env);
int		is_builtin(char **args);
int		execute_external(char **args, t_env *env);
int		execute_pipeline(t_cmd *cmd, t_env **env);
t_cmd	*parse_tokens(char **tokens);

void	execute_redirections(t_cmd *cmd);
int		apply_redirections(t_cmd *cmd, int *saved_stdin, int *saved_stdout);
void	close_all_pipes(t_cmd *cmd);
void	setup_pipe(t_cmd *current, int prev_pipe_read);
int		create_pipe(t_cmd *current);
void	restore_fd(int saved_stdin, int saved_stdout);
void	execute_child_process(t_cmd *current, t_env *env, int prev_pipe_read);

void	handle_quotes(char c, int *in_single_quotes, int *in_double_quotes);
void	detect_var(char *input, t_expand_data *data,
			int in_single_quotes, t_env *env);
void	copy_env_value(char *value, t_expand_data *data);
void	process_exit(size_t *i, t_expand_data *data, t_env *env);
void	treat_variable(char *input, t_expand_data *data);
void	expand_buffer(t_expand_data *data);

int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(void);
int		ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int		ft_exit(char **args, t_env *env);

t_env	*init_env(char **envp);
t_env	*ft_envnew(char *key, char *value);
void	ft_envadd_back(t_env **env, t_env *new);
int		ft_env(t_env *env);
void	ft_envclear(t_env **env);
char	*get_env(char *key, t_env *env);
char	*get_cmd_path(char *cmd, t_env *env);

void	free_commands(t_cmd *commands);
void	treat_error(char *msg);
void	free_args(char **args);

void	setup_signals(void);
void	init_shell(t_env **env, char **envp);
void	manage_command(char *command, t_env *env);
void	process_quotes(t_tokenizer *tk);

int		treat_output_redirect(t_cmd *cmd, char **tokens, int i);
int		treat_append_redirect(t_cmd *cmd, char **tokens, int i);
int		treat_input_redirect(t_cmd *cmd, char **tokens, int i);
void	remove_tokens(char **tokens, int start, int count);
void	parse_redirections(t_cmd *cmd, char **tokens);
void	rebuild_cmd_args(t_cmd *cmd, char **tokens);

int		count_pipes(char *command);
int		find_pipe_position(char *command, int start);
char	*extract_command(char *command, int start, int end);
int		execute_pipeline_loop(t_cmd *cmd, t_env *env);
int		fork_and_execute(t_cmd *current, t_env *env, int prev_pipe_read);
void	update_pipe(t_cmd *current, int *prev_pipe_read);
int		wait_children(t_cmd *cmd);
void	treat_double_quotes(t_tokenizer *tk);
void	treat_single_quotes(t_tokenizer *tk);
int		init_tokenizer(t_tokenizer *tk, char *input);
void	create_token(t_tokenizer *tk);
void	detect_quotes(t_tokenizer *tk);
void	treat_outside_quotes(t_tokenizer *tk);
void	treat_redirection_tokens(t_tokenizer *tk);
void	output_redir_token(t_tokenizer *tk);

char	*expand_env_vars(char *input, t_env *env);
int		take_var_name(char *input, size_t *pos, char **var_name);
void	expand_buffer(t_expand_data *data);
void	copy_exit_status(t_expand_data *data, t_env *env);
void	copy_var_value(char *result, int *j, char *value);

char	**env_to_array(t_env *env);
void	free_env_array(char **envp);

extern volatile sig_atomic_t	g_signal_received;

#endif
