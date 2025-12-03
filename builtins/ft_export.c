/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_env	*find_env_var(t_env *env, char *key)
{
	while (env && ft_strcmp(env->name, key) != 0)
		env = env->next;
	return (env);
}

static int	export_with_value(char **args, t_env **env, int i)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	t_env	*existing;

	equal_pos = ft_strchr(args[i], '=');
	key = ft_substr(args[i], 0, equal_pos - args[i]);
	value = ft_strdup(equal_pos + 1);
	existing = find_env_var(*env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
	}
	else
	{
		ft_envadd_back(env, ft_envnew(key, value));
		free(value);
	}
	free(key);
	return (0);
}

static int	export_without_value(char **args, t_env **env, int i)
{
	t_env	*existing;

	existing = find_env_var(*env, args[i]);
	if (!existing)
		ft_envadd_back(env, ft_envnew(ft_strdup(args[i]), ft_strdup("")));
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	char	*equal_pos;

	if (!args[1])
	{
		ft_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
			export_with_value(args, env, i);
		else
			export_without_value(args, env, i);
		i++;
	}
	return (0);
}
