/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:34:12 by togomez           #+#    #+#             */
/*   Updated: 2024/10/10 18:53:40 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	count;

	i = 0;
	nb = 0;
	count = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			count = -1;
		i++;
	}
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (nb * count);
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * count);
}
