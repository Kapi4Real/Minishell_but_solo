/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(t_cmd *current, t_env **env, int *connect_read)
{
	if (*connect_read != 0)
	{
		dup2(*connect_read, 0);
		close(*connect_read);
		*connect_read = 0;
	}
	execute_redirections(current);
	return (exec_builtins(current->args, env));
}

int	exec_single_cmd(t_cmd *current, t_env **env, int *connect_read)
{
	if (is_builtin(current->args) && !current->next)
		return (handle_builtin(current, env, connect_read));
	if (current->next)
	{
		if (pipe(current->pipe) == -1)
		{
			perror("minishell: pipe");
			return (0);
		}
	}
	if (!fork_and_execute(current, *env, *connect_read))
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
