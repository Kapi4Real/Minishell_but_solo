/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by student         ###   ########.fr       */
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
	while (*temp)
		result[(*j)++] = *temp++;
	free(exit_str);
}

void	copy_var_value(char *result, int *j, char *value)
{
	while (*value)
		result[(*j)++] = *value++;
}
