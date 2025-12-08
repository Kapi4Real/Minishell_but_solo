/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/12/08 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_buffer(t_expand_data *data)
{
	size_t	new_size;

	new_size = *data->size * 2;
	data->result = realloc(data->result, new_size);
	if (!data->result)
		return ;
	*data->size = new_size;
}
