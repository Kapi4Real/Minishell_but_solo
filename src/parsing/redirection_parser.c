/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_output_redirect(t_cmd *cmd, char **tokens, int i)
{
	cmd->outfile = ft_strdup(tokens[i + 1]);
	cmd->append = 0;
	remove_tokens(tokens, i, 2);
	return (i);
}

static int	handle_append_redirect(t_cmd *cmd, char **tokens, int i)
{
	cmd->outfile = ft_strdup(tokens[i + 1]);
	cmd->append = 1;
	remove_tokens(tokens, i, 2);
	return (i);
}

static int	handle_input_redirect(t_cmd *cmd, char **tokens, int i)
{
	cmd->infile = ft_strdup(tokens[i + 1]);
	remove_tokens(tokens, i, 2);
	return (i);
}

void	parse_redirections(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!tokens[i + 1])
			break ;
		if (ft_strcmp(tokens[i], ">") == 0)
			i = handle_output_redirect(cmd, tokens, i);
		else if (ft_strcmp(tokens[i], ">>") == 0)
			i = handle_append_redirect(cmd, tokens, i);
		else if (ft_strcmp(tokens[i], "<") == 0)
			i = handle_input_redirect(cmd, tokens, i);
		else
			i++;
	}
}
