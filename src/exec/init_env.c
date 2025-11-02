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
		free(temp->key);
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
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
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

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env_list;
	t_env	*new_node;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			key = ft_substr(envp[i], 0, equal_sign - envp[i]);
			value = ft_substr(envp[i], (equal_sign - envp[i]) + 1, ft_strlen(envp[i]));
			new_node = ft_envnew(key, value);
			ft_envadd_back(&env_list, new_node);
			free(key);
			free(value);
		}
		i++;
	}
	return (env_list);
}
