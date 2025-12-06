/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(char **args, t_env *env)
{
	char	*home;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home = get_env("HOME", env);
		if (!home || chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
