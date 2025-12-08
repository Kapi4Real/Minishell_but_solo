/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	treat_braced_var(char *input, size_t *pos, char **var_name)
{
	size_t	start;
	size_t	end;

	(*pos)++;
	start = *pos;
	while (input[*pos] && input[*pos] != '}')
		(*pos)++;
	if (input[*pos] != '}')
		return (0);
	end = *pos;
	if (end - start > 0)
		*var_name = ft_substr(input, start, end - start);
	else
		*var_name = NULL;
	if (*var_name == NULL)
		return (0);
	(*pos)++;
	return (1);
}

static int	treat_simple_var(char *input, size_t *pos, char **var_name)
{
	size_t	start;
	size_t	end;

	if (!input || !pos || !var_name)
		return (0);
	start = *pos;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
		(*pos)++;
	end = *pos;
	if ((ft_isalpha(input[start]) || input[start] == '_')
		&& (end - start > 0) && (end - start < 200))
	{
		*var_name = ft_substr(input, start, end - start);
		return (*var_name != NULL);
	}
	else
	{
		*var_name = NULL;
		return (0);
	}
}

int	take_var_name(char *input, size_t *pos, char **var_name)
{
	if (input[*pos] != '$')
		return (0);
	(*pos)++;
	if (input[*pos] == '{')
		return (treat_braced_var(input, pos, var_name));
	else
		return (treat_simple_var(input, pos, var_name));
}
