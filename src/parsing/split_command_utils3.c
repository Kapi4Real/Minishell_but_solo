/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	treat_double_quotes(t_tokenizer *tk)
{
	if (tk->mode == IN_DOUBLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '"')
		{
			tk->mode = OUTSIDE;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == '\0')
		{
			tk->mode = OUTSIDE;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

void	treat_single_quotes(t_tokenizer *tk)
{
	if (tk->mode == IN_SINGLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '\'')
		{
			tk->mode = OUTSIDE;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == '\0')
		{
			tk->mode = OUTSIDE;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

void	output_redir_token(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0)
		create_token(tk);
	if (tk->input[tk->pos_input + 1] == '>')
	{
		tk->tab[tk->pos_tab] = strdup(">>");
		tk->pos_tab++;
		tk->pos_input += 2;
	}
	else
	{
		tk->tab[tk->pos_tab] = strdup(">");
		tk->pos_tab++;
		tk->pos_input++;
	}
}
