/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	parse_redirections(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!tokens[i + 1])
			break ;
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			i = heredoc_redirect(cmd, tokens, i);
		}
		else if (ft_strcmp(tokens[i], ">") == 0)
		{
			create_file_redir(tokens, i);
			i = treat_output_redirect(cmd, tokens, i);
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
			i = treat_append_redirect(cmd, tokens, i);
		else if (ft_strcmp(tokens[i], "<") == 0)
			i = treat_input_redirect(cmd, tokens, i);
		else
			i++;
	}
}

static t_cmd	*manage_pipe(t_cmd *cmd, char **tokens, int *i, int *start)
{
	parse_redirections(cmd, &tokens[*start]);
	cmd->next = init_cmd();
	(*i)++;
	*start = *i;
	return (cmd->next);
}

static void	finalize_command(t_cmd *cmd, char **tokens, int start)
{
	int	k;

	parse_redirections(cmd, &tokens[start]);
	k = 0;
	while (tokens[start + k])
	{
		if (ft_strcmp(tokens[start + k], "<<") == 0)
		{
			remove_tokens(&tokens[start], k, 2);
			continue;
		}
		k++;
	}
	rebuild_cmd_args(cmd, &tokens[start]);
}

static t_cmd	*parse_tokens_loop(char **tokens, t_cmd **first_cmd,
			int *final_start)
{
	t_cmd	*cmd;
	int		i;
	int		start;

	cmd = NULL;
	i = 0;
	start = 0;
	while (tokens[i])
	{
		if (!cmd)
		{
			cmd = init_cmd();
			*first_cmd = cmd;
		}
		if (ft_strcmp(tokens[i], "|") == 0)
			cmd = manage_pipe(cmd, tokens, &i, &start);
		else
			i++;
	}
	*final_start = start;
	return (cmd);
}

t_cmd	*parse_tokens(char **tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*cmd;
	int		final_start;

	if (!tokens || !tokens[0])
		return (NULL);
	first_cmd = NULL;
	cmd = parse_tokens_loop(tokens, &first_cmd, &final_start);
	if (!cmd)
	{
		if (first_cmd)
			free_cmd(first_cmd);
		return (NULL);
	}
	finalize_command(cmd, tokens, final_start);
	return (first_cmd);
}
