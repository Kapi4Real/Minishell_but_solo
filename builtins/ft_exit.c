/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:00:00 by student          #+#    #+#             */
/*   Updated: 2025/11/18 00:00:00 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_exit_args(char **args, int *exit_code)
{
	int	is_numeric;

	is_numeric = 1;
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		is_numeric = ft_isdigit_str(args[1]);
		if (!is_numeric)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			*exit_code = 2;
		}
		else
			*exit_code = ft_atoi(args[1]);
	}
	return (0);
}

int	ft_exit(char **args, t_env *env)
{
	int	exit_code;
	int	ret;

	(void)args;
	(void)env;
	exit_code = 0;
	ret = check_exit_args(args, &exit_code);
	if (ret)
		return (ret);
	ft_envclear(&env);
	exit(exit_code);
	return (0);
}
