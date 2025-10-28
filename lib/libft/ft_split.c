/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:24:16 by togomez           #+#    #+#             */
/*   Updated: 2024/10/17 18:24:18 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	count_char_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	free_tabs(char **s, int j)
{
	size_t	i;

	i = 0;
	if (s[j] == NULL)
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;

	split = ft_calloc(ft_count_word(s, c) + 1, sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			split[j] = ft_substr(s, i, count_char_word(&s[i], c));
			if (!split[j++])
				return (free_tabs(split, j - 1), NULL);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (split);
}
