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

static int	treat_braced_var(char *input, int *pos, char **var_name)
{
	int	start;
	int	end;

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

static int	treat_simple_var(char *input, int *pos, char **var_name)
{
	int	start;
	int	end;

	if (!input || !pos || !var_name)
		return (0);
	start = *pos;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
		(*pos)++;
	end = *pos;
	if ((ft_isalpha(input[start]) || input[start] == '_')
		&& (end - start > 0) && (end - start < 200))
	{
		*var_name = malloc(end - start + 1);
		if (!*var_name)
			return (0);
		ft_strlcpy(*var_name, input + start, end - start + 1);
	}
	else
	{
		*var_name = NULL;
		return (0);
	}
	return (1);
}

int	take_var_name(char *input, int *pos, char **var_name)
{
	if (input[*pos] != '$')
		return (0);
	(*pos)++;
	if (input[*pos] == '{')
		return (treat_braced_var(input, pos, var_name));
	else
		return (treat_simple_var(input, pos, var_name));
}
