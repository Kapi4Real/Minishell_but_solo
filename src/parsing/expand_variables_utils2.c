/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_quotes(char c, int *in_single_quotes)
{
	if (c == '\'' && !*in_single_quotes)
		*in_single_quotes = 1;
	else if (c == '\'' && *in_single_quotes)
		*in_single_quotes = 0;
}

void	detect_var(char *input, t_expand_data *data,
		int in_single_quotes, t_env *env)
{
	if (input[*data->i] == '\\' && input
		[*data->i + 1] == '$' && !in_single_quotes)
	{
		(*data->i)++;
		if (*data->j >= *data->size - 1)
			expand_buffer(data);
		data->result[(*data->j)++] = input[(*data->i)++];
	}
	else if (input[*data->i] == '$' && input
		[*data->i + 1] == '?' && !in_single_quotes)
		process_exit(data->i, data, env);
	else if (input[*data->i] == '$' && !in_single_quotes)
		treat_variable(input, data);
	else
	{
		if (*data->j >= *data->size - 1)
			expand_buffer(data);
		data->result[(*data->j)++] = input[(*data->i)++];
	}
}

void	copy_env_value(char *value, t_expand_data *data)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (*data->j >= *data->size - 1)
			expand_buffer(data);
		data->result[(*data->j)++] = value[i++];
	}
}

void	process_exit(size_t *i, t_expand_data *data, t_env *env)
{
	copy_exit_status(data, env);
	(*i) += 2;
}

void	treat_variable(char *input, t_expand_data *data)
{
	char	*var_name;
	char	*value;
	size_t	old_i;

	var_name = NULL;
	old_i = *data->i;
	if (take_var_name(input, data->i, &var_name))
	{
		if (!var_name)
		{
			*data->i = old_i;
			if (*data->j >= *data->size - 1)
				expand_buffer(data);
			data->result[(*data->j)++] = input[(*data->i)++];
			return ;
		}
		value = get_env(var_name, data->env);
		if (value && *data->j < 4000)
			copy_env_value(value, data);
		free(var_name);
	}
	else
		if (*data->j < 4000)
			data->result[(*data->j)++] = input[(*data->i)++];
}
