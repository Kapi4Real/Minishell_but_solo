#include <minishell.h>

static void	execute_command(char **args, t_env *env)
{
	t_cmd	*cmd;

	if (!args || !args[0])
		return ;
	cmd = parse_tokens(args);
	if (!cmd)
		return ;
	execute_pipeline(cmd, &env);
	free_cmd(cmd);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env;
	char	*command;
	char	**args;
	t_cmd	*cmd;
	char	*test_path;

	env = init_env(envp);
	cmd = init_cmd();
	free_cmd(cmd);
	test_path = get_cmd_path("ls", env);
	free(test_path);
	while (1)
	{
		command = readline("minishell> ");
		if (command == NULL)
			break ;
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			break ;
		}
		if (strlen(command) > 0)
			add_history(command);
		args = tokenizer(command);
		if (args)
		{
			execute_command(args, env);
			free_args(args);
		}
		free(command);
	}
	ft_envclear(&env);
	fflush(stdout);
	fflush(stderr);
	return (0);
}
