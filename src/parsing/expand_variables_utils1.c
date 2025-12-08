/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_loop(char *input, t_expand_data *data, t_env *env)
{
	int	i;
	int	j;
	int	in_single_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	while (input[i])
	{
		handle_quotes(input[i], &in_single_quotes);
		data->i = &i;
		data->j = &j;
		detect_var(input, data, in_single_quotes, env);
	}
	if (j >= 4095)
		j = 4095;
	data->result[j] = '\0';
}

char	*expand_env_vars(char *input, t_env *env)
{
	t_expand_data	data;

	data.result = calloc(4096, sizeof(char));
	if (!data.result)
		return (NULL);
	data.env = env;
	expand_loop(input, &data, env);
	return (data.result);
}
