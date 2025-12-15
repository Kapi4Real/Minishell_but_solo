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

void	expand_and_quotes(char **tab, t_env *env)
{
	int		i;
	char	*expanded;
	char	*no_quotes;

	i = 0;
	while (tab[i])
	{
		expanded = expand_env_vars(tab[i], env);
		if (expanded)
		{
			free(tab[i]);
			tab[i] = expanded;
		}
		no_quotes = remove_quotes(tab[i]);
		if (no_quotes)
		{
			free(tab[i]);
			tab[i] = no_quotes;
		}
		i++;
	}
}

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
	expand_and_quotes(tk.tab, env);
	free(tk.buffer);
	return (tk.tab);
}
