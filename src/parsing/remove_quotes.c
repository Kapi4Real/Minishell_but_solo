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

static void	copy_quoted_content(char *token, int *i, char *result, int *j)
{
	char	quote_type;

	quote_type = token[*i];
	(*i)++;
	while (token[*i] && token[*i] != quote_type)
	{
		result[(*j)++] = token[(*i)++];
	}
	if (token[*i] == quote_type)
		(*i)++;
}

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
		if ((token[i] == '\'' || token[i] == '"'))
		{
			copy_quoted_content(token, &i, result, &j);
			continue ;
		}
		result[j] = token[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}
