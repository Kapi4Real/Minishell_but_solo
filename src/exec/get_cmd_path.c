#include <minishell.h>

char	*get_cmd_path(char *cmd, t_env *env)
{
	int		i;
	char	*path_str;
	char	**dir;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!cmd || !env)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, F_OK | X_OK) == 0)
				return (ft_strdup(cmd));
			else
				return (NULL);
		}
		i++;
	}
	path_str = get_env(env, "PATH");
	if (!path_str)
		return (NULL);
	dir = ft_split(path_str, ':');
	if (!dir)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		temp = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_args(dir);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_args(dir);
	return (NULL);
}
