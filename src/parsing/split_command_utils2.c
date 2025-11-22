/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <string.h>

int	init_tokenizer(t_tokenizer *tk, char *input)
{
	tk->input = input;
	tk->state = OUTSIDE;
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

void	create_token(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0)
	{
		tk->buffer[tk->pos_buffer] = '\0';
		tk->tab[tk->pos_tab] = strdup(tk->buffer);
		tk->pos_tab++;
		tk->pos_buffer = 0;
	}
}

void	handle_quotes(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '"')
	{
		tk->state = IN_DOUBLE_QUOTES;
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '\'')
	{
		tk->state = IN_SINGLE_QUOTES;
		tk->pos_input++;
	}
}

void	handle_outside(t_tokenizer *tk)
{
	if (tk->state != OUTSIDE)
		return ;
	handle_quotes(tk);
	if (tk->state != OUTSIDE)
		return ;
	if (tk->input[tk->pos_input] == ' ' || tk->input[tk->pos_input] == '\t')
	{
		create_token(tk);
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '>' || tk->input[tk->pos_input] == '<'
		|| tk->input[tk->pos_input] == '|')
		handle_redirection_tokens(tk);
	else
		tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
}

void	handle_redirection_tokens(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '>')
		handle_output_redirection_token(tk);
	else if (tk->input[tk->pos_input] == '<')
	{
		create_token(tk);
		tk->buffer[tk->pos_buffer++] = '<';
		tk->pos_input++;
		create_token(tk);
	}
	else if (tk->input[tk->pos_input] == '|')
	{
		create_token(tk);
		tk->buffer[tk->pos_buffer++] = '|';
		tk->pos_input++;
		create_token(tk);
	}
}