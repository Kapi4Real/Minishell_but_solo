/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_closed_quotes(const char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (*str == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*str == '"' && single_quote == 0)
			double_quote = !double_quote;
		str++;
	}
	return (single_quote || double_quote);
}

static void	execute_command(char **args, t_env *env)
{
	t_cmd	*cmd;
	int		exit_status;
	char	**orig_args;

	if (!args || !args[0])
		return ;
	orig_args = args;
	cmd = parse_tokens(args);
	if (!cmd)
	{
		free_args(orig_args);
		return ;
	}
	exit_status = execute_pipeline(cmd, &env);
	if (env)
		env->last_exit_status = exit_status;
	free_cmd(cmd);
	free_args(orig_args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	init_shell(t_env **env, char **envp)
{
	t_cmd	*cmd;
	char	*test_path;

	*env = init_env(envp);
	cmd = init_cmd();
	free_cmd(cmd);
	test_path = get_cmd_path("ls", *env);
	free(test_path);
	setup_signals();
}

void	manage_command(char *command, t_env *env)
{
	char	**args;
	char	*expanded_command;

	if (check_closed_quotes(command))
	{
		ft_putstr_fd("minishell: error unclosed quote\n",
			STDERR_FILENO);
		return ;
	}
	if (ft_strlen(command) > 0)
		add_history(command);
	expanded_command = command;
	args = tokenizer(expanded_command, env);
	if (args)
		execute_command(args, env);
}
