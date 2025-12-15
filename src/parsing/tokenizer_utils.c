/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_outside_quotes(t_tokenizer *tk);
static void	handle_in_double_quotes(t_tokenizer *tk);
static void	handle_in_single_quotes(t_tokenizer *tk);

static void	manage_double_quotes(t_tokenizer *tk)
{
	if (tk->mode == IN_DOUBLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '"')
		{
			tk->mode = OUTSIDE;
			tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
		}
		else
		{
			tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
		}
	}
}

static void	manage_single_quotes(t_tokenizer *tk)
{
	if (tk->mode == IN_SINGLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '\'')
		{
			tk->mode = OUTSIDE;
			tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
		}
		else
		{
			tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
		}
	}
}

void	process_quotes(t_tokenizer *tk)
{
	if (tk->mode == OUTSIDE)
		handle_outside_quotes(tk);
	else if (tk->mode == IN_DOUBLE_QUOTES)
		handle_in_double_quotes(tk);
	else if (tk->mode == IN_SINGLE_QUOTES)
		handle_in_single_quotes(tk);
}
