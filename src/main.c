#include "minishell.h"

static void	execute_command(char **args)
{
	if (is_builtin(args))
		exec_builtins(args);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	main(void)
{
	char	command[100];
	char	**args;

	while (1)
	{
		printf("minishell> ");
		fflush(stdout);
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;
		command[strcspn(command, "\n")] = '\0';
		if (strcmp(command, "exit") == 0)
			break;
		args = tokenizer(command);
		for (int j = 0; args[j]; j++)
			printf("[%s] ", args[j]);
		printf("\n");
		if (args)
		{
			execute_command(args);
			free_args(args);
		}
	}
	return (0);
}
