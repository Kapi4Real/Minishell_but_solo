/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->pipe[0] > 2)
			close(tmp->pipe[0]);
		if (tmp->pipe[1] > 2)
			close(tmp->pipe[1]);
		tmp = tmp->next;
	}
}

void	setup_pipe(t_cmd *current, int prev_pipe_read)
{
	if (prev_pipe_read != 0 && !current->infile)
	{
		dup2(prev_pipe_read, STDIN_FILENO);
		close(prev_pipe_read);
	}
	if (current->next)
	{
		close(current->pipe[0]);
		dup2(current->pipe[1], STDOUT_FILENO);
		close(current->pipe[1]);
	}
}

int	create_pipe(t_cmd *current)
{
	if (current->next)
	{
		if (pipe(current->pipe) == -1)
		{
			perror("minishell: pipe");
			return (0);
		}
	}
	return (1);
}

void	execute_child_process(t_cmd *current, t_env *env, int prev_pipe_read)
{
	int	ret;

	execute_redirections(current);
	setup_pipe(current, prev_pipe_read);
	if (is_builtin(current->args))
		exit(exec_builtins(current->args, &env));
	else
	{
		ret = execute_external(current->args, env);
		exit(ret);
	}
}
