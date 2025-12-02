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

static void	run_shell_loop(t_env *env)
{
	char	*command;

	while (1)
	{
		command = readline("minishell> ");
		if (command == NULL)
		{
			printf("exit\n");
			break ;
		}
		g_signal_received = 0;
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		process_command(command, env);
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
