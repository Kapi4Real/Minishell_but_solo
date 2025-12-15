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
	size_t	i;
	size_t	j;
	int		in_single_quotes;
	int		in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (input[i])
	{
		handle_quotes(input[i], &in_single_quotes, &in_double_quotes);
		data->i = &i;
		data->j = &j;
		detect_var(input, data, in_single_quotes, env);
	}
	data->result[j] = '\0';
}

char	*expand_env_vars(char *input, t_env *env)
{
	t_expand_data	data;
	size_t			size;

	size = 1024;
	data.result = calloc(size, sizeof(char));
	if (!data.result)
		return (NULL);
	data.env = env;
	data.size = &size;
	expand_loop(input, &data, env);
	return (data.result);
}
