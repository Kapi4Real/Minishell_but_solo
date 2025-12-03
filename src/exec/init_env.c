/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_envclear(t_env **env)
{
	t_env	*temp;
	t_env	*next;

	if (!env || !*env)
		return ;
	temp = *env;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
	*env = NULL;
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->last_exit_status = 0;
	new_node->next = NULL;
	return (new_node);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static void	process_env_var(char *env_str, t_env **env_list)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*new_node;
	int		len;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		key = ft_substr(env_str, 0, equal_sign - env_str);
		len = ft_strlen(env_str);
		value = ft_substr(env_str, (equal_sign - env_str) + 1, len);
		new_node = ft_envnew(key, value);
		ft_envadd_back(env_list, new_node);
		free(key);
		free(value);
	}
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		process_env_var(envp[i], &env_list);
		i++;
	}
	return (env_list);
}
