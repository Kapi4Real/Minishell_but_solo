#include <minishell.h>

char	*remove_quotes(char *token)
{
	int		i;
	int		j;
	char	*result;

	if (!token)
		return (NULL);
	result = malloc(ft_strlen(token) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			i++;
			continue ;
		}
		result[j] = token[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
