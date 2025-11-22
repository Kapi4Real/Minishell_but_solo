/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static t_cmd	*handle_pipe(t_cmd *cmd, char **tokens, int *i, int *start)
{
	tokens[*i] = NULL;
	parse_redirections(cmd, &tokens[*start]);
	rebuild_cmd_args(cmd, &tokens[*start]);
	cmd->next = init_cmd();
	(*i)++;
	*start = *i;
	return (cmd->next);
}

static void	finalize_command(t_cmd *cmd, char **tokens, int start)
{
	parse_redirections(cmd, &tokens[start]);
	rebuild_cmd_args(cmd, &tokens[start]);
}

static t_cmd	*parse_tokens_loop(char **tokens, t_cmd **first_cmd)
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
			cmd = handle_pipe(cmd, tokens, &i, &start);
		else
			i++;
	}
	return (cmd);
}

t_cmd	*parse_tokens(char **tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*cmd;

	if (!tokens || !tokens[0])
		return (NULL);
	first_cmd = NULL;
	cmd = parse_tokens_loop(tokens, &first_cmd);
	if (!cmd)
		return (NULL);
	finalize_command(cmd, tokens, 0);
	return (first_cmd);
}
