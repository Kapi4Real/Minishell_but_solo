#include <minishell.h>

int	exec_builtins(char **args)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	/*
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env());
	*/
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	/*
	else if (ft_strcmp(args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(args[0], "env") == 0)
		return (1);
	*/
	else if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}
