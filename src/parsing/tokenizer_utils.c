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

static void	manage_double_quotes(t_tokenizer *tk)
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

static void	manage_single_quotes(t_tokenizer *tk)
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

void	process_quotes(t_tokenizer *tk)
{
	if (tk->input[tk->pos_input] == '"' && tk->mode == OUTSIDE)
	{
		tk->mode = IN_DOUBLE_QUOTES;
		tk->pos_input++;
	}
	else if (tk->input[tk->pos_input] == '\'' && tk->mode == OUTSIDE)
	{
		tk->mode = IN_SINGLE_QUOTES;
		tk->pos_input++;
	}
	else
	{
		treat_double_quotes(tk);
		treat_single_quotes(tk);
	}
}
