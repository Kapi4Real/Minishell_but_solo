/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_exit(int *i, char *result, int *j, t_env *env)
{
	copy_exit_status(result, j, env);
	(*i) += 2;
}

static void	process_variable(char *input, t_expand_data *data)
{
	char	*var_name;

	var_name = NULL;
	if (take_var_name(input, data->i, &var_name))
	{
		if (get_env(data->env, var_name))
			copy_var_value(data->result, data->j, get_env(data->env, var_name));
		free(var_name);
	}
	else
	{
		data->result[(*data->j)++] = input[(*data->i)++];
	}
}

static void	init_expand_data(t_expand_data *data, int *i, int *j, t_env *env)
{
	data->result = malloc(sizeof(char) * 2048);
	*i = 0;
	*j = 0;
	data->i = i;
	data->j = j;
	data->env = env;
}

char	*expand_env_vars(char *input, t_env *env)
{
	t_expand_data	data;
	int				i;
	int				j;
	int				in_single_quotes;

	init_expand_data(&data, &i, &j, env);
	in_single_quotes = 0;
	if (!data.result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !in_single_quotes)
			in_single_quotes = 1;
		else if (input[i] == '\'' && in_single_quotes)
			in_single_quotes = 0;
		if (input[i] == '$' && input[i + 1] == '?' && !in_single_quotes)
			process_exit(&i, data.result, &j, env);
		else if (input[i] == '$' && !in_single_quotes)
			process_variable(input, &data);
		else
			data.result[j++] = input[i++];
	}
	data.result[j] = '\0';
	return (data.result);
}
