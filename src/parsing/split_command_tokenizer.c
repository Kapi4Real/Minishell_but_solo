/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_tokenizer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <string.h>

char	**tokenizer(char *input, t_env *env)
{
	t_tokenizer	tk;

	if (!input || !init_tokenizer(&tk, input))
		return (NULL);
	while (input[tk.pos_input] && tk.pos_tab < 99)
	{
		treat_outside_quotes(&tk);
		treat_double_quotes(&tk);
		treat_single_quotes(&tk);
	}
	create_token(&tk);
	tk.tab[tk.pos_tab] = NULL;
	expand_tokens(tk.tab, env);
	free(tk.buffer);
	return (tk.tab);
}
