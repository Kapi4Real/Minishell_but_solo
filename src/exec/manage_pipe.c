/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	handle_input_execution(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_output_execution(t_cmd *cmd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	execute_redirections(t_cmd *cmd)
{
	if (cmd->infile)
		handle_input_execution(cmd);
	if (cmd->outfile)
		handle_output_execution(cmd);
}

static int	handle_input_redirection(t_cmd *cmd, int *saved_stdin)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	*saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirection(t_cmd *cmd, int *saved_stdout)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd, int *saved_stdin, int *saved_stdout)
{
	if (!cmd || !saved_stdin || !saved_stdout)
		return (1);
	*saved_stdin = -1;
	*saved_stdout = -1;
	if (cmd->infile && handle_input_redirection(cmd, saved_stdin))
		return (1);
	if (cmd->outfile)
	{
		if (handle_output_redirection(cmd, saved_stdout))
		{
			if (*saved_stdin != -1)
			{
				dup2(*saved_stdin, STDIN_FILENO);
				close(*saved_stdin);
				*saved_stdin = -1;
			}
			return (1);
		}
	}
	return (0);
}

void	restore_redirections_parent(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

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
	if (prev_pipe_read != 0)
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

	setup_pipe(current, prev_pipe_read);
	execute_redirections(current);
	if (is_builtin(current->args))
		exit(exec_builtins(current->args, env));
	else
	{
		ret = execute_external(current->args, env);
		exit(ret);
	}
}
