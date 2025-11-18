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

static void	rebuild_cmd_args(t_cmd *cmd, char **tokens)
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

static void	remove_tokens(char **tokens, int start, int count)
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

void	parse_redirections(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!tokens[i + 1])
			break ;
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			cmd->outfile = ft_strdup(tokens[i + 1]);
			cmd->append = 0;
			remove_tokens(tokens, i, 2);
		}
		else	if (ft_strcmp(tokens[i], ">>") == 0)
		{
			cmd->outfile = ft_strdup(tokens[i + 1]);
			cmd->append = 1;
			remove_tokens(tokens, i, 2);
		}
		else	if (ft_strcmp(tokens[i], "<") == 0)
		{
			cmd->infile = ft_strdup(tokens[i + 1]);
			remove_tokens(tokens, i, 2);
		}
		else
			i++;
	}
}

t_cmd	*parse_tokens(char **tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*cmd;
	int		i;
	int		start;

	if (!tokens || !tokens[0])
		return (NULL);
	first_cmd = NULL;
	cmd = NULL;
	i = 0;
	start = 0;
	while (tokens[i])
	{
		if (!cmd)
		{
			cmd = init_cmd();
			first_cmd = cmd;
		}
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			tokens[i] = NULL;
			parse_redirections(cmd, &tokens[start]);
			rebuild_cmd_args(cmd, &tokens[start]);
			cmd->next = init_cmd();
			cmd = cmd->next;
			i++;
			start = i;
		}
		else
		{
			i++;
		}
	}
	if (!cmd)
		return (NULL);
	parse_redirections(cmd, &tokens[start]);
	rebuild_cmd_args(cmd, &tokens[start]);
	return (first_cmd);
}
