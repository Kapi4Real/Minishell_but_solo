#include <minishell.h>
#include <limits.h>

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

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDERR_FILENO, "minishell: pwd: ", 16);
		perror("");
	}
	return (0);
}
/*
int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s", envp[i]);
		i++;
	}
	return (0);
}*/

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

/*
int	ft_export(char **args)
{
	char	*equal;
	char	*value;

	if (!args[1])
		return (ft_env(g_env));
	equal = ft_strchr(args[1], '=');
	if (equal)
	{
		*equal = '\0';
		value = equal + 1;
		if (setenv(args[1], value, 1) == -1)
		{
			perror("export");
			return (1);
		}
	}
	return (0);
}

int	ft_unset(char **args)
{
	if (!args[1])
		return (0);
	if (unsetenv(args[1]) == -1)
	{
		perror("unset");
		return (1);
	}
	return (0);
}

*/ 

int	ft_exit(char **args)
{
	int	exit_code;
	int	is_numeric;

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
	exit(exit_code);
}

