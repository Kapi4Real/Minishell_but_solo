/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_pipes(char *command)
{
	int	i;
	int	count;
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
			in_quotes = !in_quotes;
		if (!in_quotes && command[i] == '|')
			count++;
		i++;
	}
	return (count + 1);
}

int	find_pipe_position(char *command, int start)
{
	int	i;
	int	in_quotes;

	i = start;
	in_quotes = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
			in_quotes = !in_quotes;
		if (!in_quotes && command[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

char	*extract_command(char *command, int start, int end)
{
	char	*part;
	int		len;
	int		i;

	while (start < end && command[start] == ' ')
		start++;
	while (end > start && command[end - 1] == ' ')
		end--;
	len = end - start;
	part = malloc(len + 1);
	if (!part)
		return (NULL);
	i = 0;
	while (i < len)
	{
		part[i] = command[start + i];
		i++;
	}
	part[len] = '\0';
	return (part);
}

void	create_token(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0 && tk->pos_tab < 99)
	{
		tk->buffer[tk->pos_buffer] = '\0';
		tk->tab[tk->pos_tab] = strdup(tk->buffer);
		tk->pos_tab++;
		tk->pos_buffer = 0;
	}
}
