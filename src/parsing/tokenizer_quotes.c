/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outside_quotes(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '"')
	{
		tk->mode = IN_DOUBLE_QUOTES;
		tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
	}
	else if (tk->input[tk->pos_input] == '\'')
	{
		tk->mode = IN_SINGLE_QUOTES;
		tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
	}
	else
	{
		tk->buffer[tk->pos_buffer++] = tk->input[tk->pos_input++];
	}
}

void	handle_in_double_quotes(t_tokenizer *tk)
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

void	handle_in_single_quotes(t_tokenizer *tk)
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
