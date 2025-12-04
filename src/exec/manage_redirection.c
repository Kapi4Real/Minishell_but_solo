/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	treat_input_execution(t_cmd *cmd)
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

static void	treat_output_execution(t_cmd *cmd)
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
		treat_input_execution(cmd);
	if (cmd->outfile)
		treat_output_execution(cmd);
}
