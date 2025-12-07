/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_only_spaces(const char *command)
{
	int	j;

	j = 0;
	while (command && command[j])
	{
		if (!ft_isspace(command[j]))
			return (0);
		j++;
	}
	return (1);
}

static int	is_exit_command(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

static void	run_shell_loop(t_env *env)
{
	char	*command;

	while (1)
	{
		command = NULL;
		if (isatty(STDIN_FILENO))
			command = readline("minishell> ");
		else
			command = readline("");
		if (command == NULL)
		{
			printf("exit\n");
			break ;
		}
		g_signal_received = 0;
		if (is_exit_command(command))
		{
			free(command);
			break ;
		}
		if (!is_only_spaces(command) && command && ft_strlen(command) > 0)
			manage_command(command, env);
		free(command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	init_shell(&env, envp);
	run_shell_loop(env);
	ft_envclear(&env);
	fflush(stdout);
	fflush(stderr);
	return (0);
}
