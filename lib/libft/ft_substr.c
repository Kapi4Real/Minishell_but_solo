/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:11:27 by togomez           #+#    #+#             */
/*   Updated: 2024/10/14 19:11:29 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	return (new);
}
