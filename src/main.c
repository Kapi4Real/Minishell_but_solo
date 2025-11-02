#include <minishell.h>

static void	execute_command(char **args, t_env *env)
{
	if (is_builtin(args))
		exec_builtins(args, env);
	else
		printf("env reconnu\n");
}

void	free_args(char **args)
{
	int	i;

	printf("DEBUG: free_args appelé - %p\n", (void *)args);
	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		printf("DEBUG: Free arg[%d] = %p ('%s')\n", i, (void *)args[i], args[i]);
		free(args[i]);
		i++;
	}
	printf("DEBUG: Free args array\n");
	free(args);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	command[100];
	char	**args;
	t_cmd	*cmd;
	char	*test_path;

	env = init_env(envp);
	cmd = init_cmd();
	free_cmd(cmd);
	test_path = get_cmd_path("ls", env);
	printf("Chemin trouvé pour 'ls': %s\n", test_path);
	free(test_path);
	printf("DEBUG: Environnement initialisé - %p\n", (void *)env);
	while (1)
	{
		printf("minishell> ");
		fflush(stdout);
		if (fgets(command, sizeof(command), stdin) == NULL)
			break ;
		command[strcspn(command, "\n")] = '\0';
		if (strcmp(command, "exit") == 0)
			break ;
		args = tokenizer(command);
		for (int j = 0; args[j]; j++)
			printf("[%s] ", args[j]);
		printf("\n");
		if (args)
		{
			execute_command(args, env);
			free_args(args);
		}
	}
	ft_envclear(&env);
	fflush(stdout);
	fflush(stderr);
	return (0);
}
