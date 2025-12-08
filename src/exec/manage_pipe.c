/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kapi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:00:00 by kapi              #+#    #+#             */
/*   Updated: 2025/12/04 00:00:00 by kapi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_execute(t_cmd *current, t_env *env, int connect_read)
{
	current->pid = fork();
	if (current->pid == 0)
		execute_child_process(current, env, connect_read);
	else if (current->pid < 0)
	{
		perror("minishell: fork");
		return (0);
	}
	return (1);
}

void	update_pipe(t_cmd *current, int *connect_read)
{
	if (*connect_read != 0)
		close(*connect_read);
	if (current->next)
	{
		close(current->pipe[1]);
		*connect_read = current->pipe[0];
	}
	else
		*connect_read = 0;
}

int	wait_children(t_cmd *cmd)
{
	int		status;
	int		last_status;
	t_cmd	*current;

	current = cmd;
	last_status = 0;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (!current->next)
			last_status = WEXITSTATUS(status);
		current = current->next;
	}
	return (last_status);
}

static int	exec_single_cmd(t_cmd *current, t_env **env, int *connect_read)
{
	if (current->next)
	{
		if (pipe(current->pipe) == -1)
		{
			perror("minishell: pipe");
			return (0);
		}
	}
	if (!fork_and_execute(current,
			*env, *connect_read))
		return (0);
	if (*connect_read != 0)
		close(*connect_read);
	if (current->next)
	{
		close(current->pipe[1]);
		*connect_read = current->pipe[0];
	}
	else
	{
		*connect_read = 0;
	}
	return (1);
}

int	execute_pipeline(t_cmd *cmd, t_env **env)
{
	int		connect_read;
	t_cmd	*current;
	int		exit_status;

	connect_read = 0;
	current = cmd;
	while (current)
	{
		if (!exec_single_cmd(current, env, &connect_read))
			return (1);
		current = current->next;
	}
	exit_status = wait_children(cmd);
	close_all_pipes(cmd);
	return (exit_status);
}
