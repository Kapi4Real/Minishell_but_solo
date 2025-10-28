/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:52:50 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:22:20 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*g_save_ptr = NULL;

static char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
		str++;
	return (str);
}

static char	*find_token_end(char *str, const char *delim)
{
	while (*str && !ft_strchr(delim, *str))
		str++;
	return (str);
}

static void	update_save_ptr(char *token_end)
{
	if (*token_end != '\0')
		g_save_ptr = token_end + 1;
	else
		g_save_ptr = NULL;
}

char	*ft_strtok(char *str, const char *delim)
{
	char	*token_start;
	char	*token_end;

	if (str == NULL)
	{
		if (g_save_ptr == NULL)
			return (NULL);
		str = g_save_ptr;
	}
	str = skip_delimiters(str, delim);
	if (*str == '\0')
	{
		g_save_ptr = NULL;
		return (NULL);
	}
	token_start = str;
	token_end = find_token_end(str, delim);
	if (token_end != str)
		*token_end = '\0';
	update_save_ptr(token_end);
	return (token_start);
}