/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_array_loop(char **tab_env, t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tab_env[i] = ft_strjoin3(tmp->name, "=", tmp->value);
		if (!tab_env[i])
		{
			while (i--)
				free(tab_env[i]);
			return (0);
		}
		i++;
		tmp = tmp->next;
	}
	tab_env[i] = NULL;
	return (1);
}

char	**env_to_array(t_env *env)
{
	int		size;
	char	**tab_env;

	size = ft_lstsize((t_list *)env);
	tab_env = malloc(sizeof(char *) * (size + 1));
	if (!tab_env)
		return (NULL);
	if (!env_array_loop(tab_env, env))
	{
		free(tab_env);
		return (NULL);
	}
	return (tab_env);
}

void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
