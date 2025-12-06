/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

void	create_file_redir(char **tokens, int i)
{
	int	fd;

	fd = -1;
	if (tokens[i + 2] && ft_strcmp(tokens[i + 2], ">") == 0)
	{
		fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
	}
}
