/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:27:35 by togomez           #+#    #+#             */
/*   Updated: 2024/10/10 18:49:43 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	length = ft_strlen(src);
	i = 0;
	while (src[i] != '\0' && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > length)
		dst[i] = 0;
	else
		dst[i - 1] = 0;
	return (length);
}
