/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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

static int	execute_single_builtin(t_cmd *cmd, t_env **env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = -1;
	saved_stdout = -1;
	if (apply_redirections(cmd, &saved_stdin, &saved_stdout) != 0)
		return (1);
	result = exec_builtins(cmd->args, *env);
	restore_redirections_parent(saved_stdin, saved_stdout);
	return (result);
}

static int	execute_pipeline_loop(t_cmd *cmd, t_env **env)
{
	t_cmd	*current;
	int		prev_pipe_read;
	int		j;

	current = cmd;
	prev_pipe_read = 0;
	while (current)
	{
		j = 0;
		while (current->args && current->args[j])
			j++;
		if (!create_pipe(current))
			return (1);
		if (!fork_and_execute(current, *env, prev_pipe_read))
			return (1);
		update_pipe(current, &prev_pipe_read);
		current = current->next;
	}
	return (wait_children(cmd));
}

int	execute_pipeline(t_cmd *cmd, t_env **env)
{
	int	result;

	if (!cmd)
		return (1);
	if (!cmd->next && is_builtin(cmd->args))
		return (execute_single_builtin(cmd, env));
	result = execute_pipeline_loop(cmd, env);
	close_all_pipes(cmd);
	return (result);
}
