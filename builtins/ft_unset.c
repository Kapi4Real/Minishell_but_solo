/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_env_node(t_env **env, t_env *current, t_env *prev)
{
	if (prev)
		prev->next = current->next;
	else
		*env = current->next;
	free(current->name);
	free(current->value);
	free(current);
}

static int	unset_single_var(char *var_name, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			remove_env_node(env, current, prev);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (!args[1] || !env || !*env)
		return (0);
	i = 1;
	while (args[i])
	{
		unset_single_var(args[i], env);
		i++;
	}
	return (0);
}
