/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "minishell.h"

static char	*supp_space(const char *str)
{
	char	*res;
	size_t	len;

	while (*str == ' ' || *str == '\t')
		str++;
	len = strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	strncpy(res, str, len);
	res[len] = '\0';
	return (res);
}

static void	read_heredoc(int pipe_fd, char *exit_word)
{
	char	*line;
	char	*deleted;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		deleted = supp_space(line);
		if (deleted && strcmp(deleted, exit_word) == 0)
		{
			free(deleted);
			free(line);
			break ;
		}
		write(pipe_fd, line, strlen(line));
		write(pipe_fd, "\n", 1);
		free(deleted);
		free(line);
	}
}

int	heredoc_redirect(t_cmd *cmd, char **tokens, int i)
{
	int		pipe_heredoc[2];
	char	*exit_word;

	if (cmd->heredoc_fd >= 0)
		return (i);
	exit_word = tokens[i + 1];
	if (pipe(pipe_heredoc) == -1)
		return (i);
	read_heredoc(pipe_heredoc[1], exit_word);
	close(pipe_heredoc[1]);
	cmd->heredoc_fd = pipe_heredoc[0];
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	return (i + 2);
}
