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

static int	env_list_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_to_array(t_env *env)
{
	int		size;
	char	**arr;
	int		i;
	t_env	*tmp;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		arr[i] = ft_strjoin3(tmp->name, "=", tmp->value);
		if (!arr[i])
		{
			while (i--)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}