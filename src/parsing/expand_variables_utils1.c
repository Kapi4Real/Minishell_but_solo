/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/25 00:00:00 by student         ###   ########.fr       */
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

	start = *pos;
	while (input[*pos] && (ft_isalnum(input[*pos]) || input[*pos] == '_'))
		(*pos)++;
	end = *pos;
	if ((ft_isalpha(input[start]) || input[start] == '_') && (end - start > 0))
		*var_name = ft_substr(input, start, end - start);
	else
		*var_name = NULL;
	if (*var_name == NULL)
		return (0);
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
