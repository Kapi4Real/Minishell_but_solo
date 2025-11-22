/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
