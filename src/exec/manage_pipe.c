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

int	fork_and_execute(t_cmd *current, t_env *env, int prev_pipe_read)
{
	current->pid = fork();
	if (current->pid == 0)
		execute_child_process(current, env, prev_pipe_read);
	else if (current->pid < 0)
	{
		perror("minishell: fork");
		return (0);
	}
	return (1);
}

void	update_pipe(t_cmd *current, int *prev_pipe_read)
{
	if (*prev_pipe_read != 0)
		close(*prev_pipe_read);
	if (current->next)
	{
		close(current->pipe[1]);
		*prev_pipe_read = current->pipe[0];
	}
	else
		*prev_pipe_read = 0;
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

int execute_pipeline(t_cmd *cmd, t_env **env)
{
	int prev_pipe_read = 0;
	t_cmd *current = cmd;
	int result = 0;

	while (current)
	{
		if (current->next)
		{
			if (pipe(current->pipe) == -1)
			{
				perror("minishell: pipe");
				return (1);
			}
		}
		if (!fork_and_execute(current, *env, prev_pipe_read))
			return (1);
		if (prev_pipe_read != 0)
			close(prev_pipe_read);
		if (current->next)
		{
			close(current->pipe[1]);
			prev_pipe_read = current->pipe[0];
		}
		else
		{
			prev_pipe_read = 0;
		}
		current = current->next;
	}
	result = wait_children(cmd);
	close_all_pipes(cmd);
	return (result);
}
