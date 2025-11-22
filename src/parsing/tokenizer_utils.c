/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_double_quotes(t_tokenizer *tk)
{
	if (tk->state == IN_DOUBLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '"')
		{
			tk->state = OUTSIDE;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == '\0')
		{
			tk->state = OUTSIDE;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

static void	handle_single_quotes(t_tokenizer *tk)
{
	if (tk->state == IN_SINGLE_QUOTES)
	{
		if (tk->input[tk->pos_input] == '\'')
		{
			tk->state = OUTSIDE;
			tk->pos_input++;
		}
		else if (tk->input[tk->pos_input] == '\0')
		{
			tk->state = OUTSIDE;
		}
		else
		{
			tk->buffer[tk->pos_buffer] = tk->input[tk->pos_input];
			tk->pos_buffer++;
			tk->pos_input++;
		}
	}
}

void	process_quotes(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '"' && tk->state == OUTSIDE)
	{
		tk->state = IN_DOUBLE_QUOTES;
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '\'' && tk->state == OUTSIDE)
	{
		tk->state = IN_SINGLE_QUOTES;
		tk->pos_input++;
	}
	else
	{
		handle_double_quotes(tk);
		handle_single_quotes(tk);
	}
}
