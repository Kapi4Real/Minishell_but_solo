/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe2_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

static void	treat_input_child(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: input redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	treat_output_child(t_cmd *cmd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: output redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	setup_child_redirections(t_cmd *cmd)
{
	if (cmd->infile)
		treat_input_child(cmd);
	if (cmd->outfile)
		treat_output_child(cmd);
}

int	execute_pipeline_loop(t_cmd *cmd, t_env *env)
{
	t_cmd	*current;
	int		prev_pipe_read;

	current = cmd;
	prev_pipe_read = 0;
	while (current)
	{
		if (!create_pipe(current))
			return (1);
		if (!fork_and_execute(current, env, prev_pipe_read))
			return (1);
		update_pipe(current, &prev_pipe_read);
		current = current->next;
	}
	return (wait_children(cmd));
}
