/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_token(t_tokenizer *tk)
{
	if (tk->pos_buffer > 0 && tk->pos_tab < 99)
	{
		tk->buffer[tk->pos_buffer] = '\0';
		tk->tab[tk->pos_tab] = strdup(tk->buffer);
		tk->pos_tab++;
		tk->pos_buffer = 0;
	}
}
