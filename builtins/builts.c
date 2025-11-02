#include <minishell.h>

int	ft_echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int	ft_cd(char **args)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (chdir(getenv("HOME")) != 0)
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

int	ft_exit(char **args, t_env *env)
{
	int	exit_code;
	int	is_numeric;

	(void)args;
	(void)env;
	exit_code = 0;
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
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(args[1]);
	}
	ft_envclear(&env);
	exit(exit_code);
	return (0);
}

int	ft_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		fflush(stdout);
		env = env->next;
	}
	return (0);
}
