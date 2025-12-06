/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	copy_exit_status(char *result, int *j, t_env *env)
{
	char	*exit_str;
	char	*temp;
	int		exit_status;

	exit_status = 0;
	if (env)
		exit_status = env->last_exit_status;
	exit_str = ft_itoa(exit_status);
	temp = exit_str;
	while (*temp && *j < 8190)
		result[(*j)++] = *temp++;
	free(exit_str);
}

void	copy_var_value(char *result, int *j, char *value)
{
	int	len;

	len = 0;
	while (*value && *j < 4000 && len < 500)
	{
		result[(*j)++] = *value++;
		len++;
	}
}

void	expand_tokens(char **tokens, t_env *env)
{
	int	i;
	char *new;

	i = 0;
	while (tokens[i])
	{
		new = expand_env_vars(tokens[i], env);
		if (new)
		{
			free(tokens[i]);
			tokens[i] = new;
		}
		i++;
	}
}
