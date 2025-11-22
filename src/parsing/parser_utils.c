/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_output_redirect(t_cmd *cmd, char **tokens, int i)
{
	cmd->outfile = ft_strdup(tokens[i + 1]);
	cmd->append = 0;
	remove_tokens(tokens, i, 2);
	return (i);
}

int	handle_append_redirect(t_cmd *cmd, char **tokens, int i)
{
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

int	handle_input_redirect(t_cmd *cmd, char **tokens, int i)
{
	cmd->infile = ft_strdup(tokens[i + 1]);
	remove_tokens(tokens, i, 2);
	return (i);
}

void	rebuild_cmd_args(t_cmd *cmd, char **tokens)
{
	int	i;
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	if (cmd->args)
		free_args(cmd->args);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		cmd->args[i] = ft_strdup(tokens[i]);
		i++;
	}
	cmd->args[count] = NULL;
}