/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:01:23 by togomez           #+#    #+#             */
/*   Updated: 2024/10/10 19:09:03 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str2;
	unsigned char	ch;

	ch = (unsigned char)c;
	str2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str2[i] = ch;
		i++;
	}
	return (s);
}
