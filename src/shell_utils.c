/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execute_command(char **args, t_env *env)
{
	t_cmd	*cmd;
	int		exit_status;

	if (!args || !args[0])
		return ;
	cmd = parse_tokens(args);
	if (!cmd)
		return ;
	exit_status = execute_pipeline(cmd, &env);
	if (env)
		env->last_exit_status = exit_status;
	free_cmd(cmd);
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

void	process_command(char *command, t_env *env)
{
	char	**args;
	char	*expanded_command;

	if (strlen(command) > 0)
		add_history(command);
	expanded_command = expand_env_vars(command, env);
	if (!expanded_command)
		return ;
	args = tokenizer(expanded_command);
	if (args)
	{
		execute_command(args, env);
		free_args(args);
	}
	free(expanded_command);
}
