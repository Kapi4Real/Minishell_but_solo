/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_tokenizer(t_tokenizer *tk, char *input)
{
	tk->input = input;
	tk->mode = OUTSIDE;
	tk->buffer = malloc(sizeof(char) * 100);
	if (!tk->buffer)
		return (0);
	tk->tab = malloc(sizeof(char *) * 100);
	if (!tk->tab)
	{
		free(tk->buffer);
		return (0);
	}
	tk->pos_input = 0;
	tk->pos_buffer = 0;
	tk->pos_tab = 0;
	return (1);
}

void	detect_quotes(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '"')
	{
		tk->mode = IN_DOUBLE_QUOTES;
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '\'')
	{
		tk->mode = IN_SINGLE_QUOTES;
		tk->pos_input++;
	}
}

void	treat_outside_quotes(t_tokenizer *tk)
{
	if (tk->mode != OUTSIDE)
		return ;
	detect_quotes(tk);
	if (tk->mode != OUTSIDE)
		return ;
	if (tk->input[tk->pos_input] == ' ' || tk->input[tk->pos_input] == '\t')
	{
		create_token(tk);
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '>' || tk->input[tk->pos_input] == '<'
		|| tk->input[tk->pos_input] == '|')
		treat_redirection_tokens(tk);
	else
		tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
}

static void	treat_input_redir(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0)
		create_token(tk);
	if (tk->input[tk->pos_input + 1] == '<')
	{
		tk->tab[tk->pos_tab] = strdup("<<");
		tk->pos_tab++;
		tk->pos_input += 2;
	}
	else
	{
		tk->tab[tk->pos_tab] = strdup("<");
		tk->pos_tab++;
		tk->pos_input++;
	}
}

void	treat_redirection_tokens(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '>')
		output_redir_token(tk);
	else if (tk->input[tk->pos_input] == '<')
		treat_input_redir(tk);
	else if (tk->input[tk->pos_input] == '|')
	{
		if (tk->pos_buffer > 0)
			create_token(tk);
		tk->tab[tk->pos_tab] = strdup("|");
		tk->pos_tab++;
		tk->pos_input++;
	}
}
