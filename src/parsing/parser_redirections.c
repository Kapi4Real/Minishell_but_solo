/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	treat_output_redirect(t_cmd *cmd, char **tokens, int i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(tokens[i + 1]);
	cmd->append = 0;
	remove_tokens(tokens, i, 2);
	return (i);
}

int	treat_append_redirect(t_cmd *cmd, char **tokens, int i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup(tokens[i + 1]);
	cmd->append = 1;
	remove_tokens(tokens, i, 2);
	return (i);
}

void	remove_tokens(char **tokens, int start, int count)
{
	int	i;
	int	j;

	if (!tokens || !tokens[start])
		return ;
	j = 0;
	while (j < count && tokens[start + j])
	{
		free(tokens[start + j]);
		j++;
	}
	i = start;
	while (tokens[start + j])
	{
		tokens[i] = tokens[start + j];
		i++;
		j++;
	}
	tokens[i] = NULL;
}

int	treat_input_redirect(t_cmd *cmd, char **tokens, int i)
{
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = ft_strdup(tokens[i + 1]);
	remove_tokens(tokens, i, 2);
	return (i);
}

void	rebuild_cmd_args(t_cmd *cmd, char **tokens)
{
	int	i;
	int	count;
	int	j;

	count = 0;
	while (tokens[count] && ft_strcmp(tokens[count], "|") != 0)
		count++;
	if (cmd->args)
		free_args(cmd->args);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (i < count)
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			i += 2;
			continue ;
		}
		cmd->args[j] = ft_strdup(tokens[i]);
		j++;
		i++;
	}
	cmd->args[j] = NULL;
}
