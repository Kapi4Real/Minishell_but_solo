#include <minishell.h>

char	*get_env(t_env *env, char *key)
{
	t_env	*current;

	if (!env || !key)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
