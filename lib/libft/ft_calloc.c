/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:42:29 by togomez           #+#    #+#             */
/*   Updated: 2024/10/14 18:42:37 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*a;
	size_t	tot;

	tot = nmemb * size;
	if (tot == 0)
		return (malloc (0));
	else if (tot / size != nmemb)
		return (NULL);
	a = malloc(tot);
	if (!a)
		return (NULL);
	ft_bzero(a, tot);
	return (a);
}
