/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*treat_abs_path(char *cmd)
{
	int	i;

	i = 0;
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
	return (NULL);
}

static char	*search_in_path(char *cmd, char **dirs)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	*path_str;
	char	**dirs;
	char	*result;

	if (!cmd || !env)
		return (NULL);
	result = treat_abs_path(cmd);
	if (result != NULL)
		return (result);
	path_str = get_env(env, "PATH");
	if (!path_str)
		return (NULL);
	dirs = ft_split(path_str, ':');
	if (!dirs)
		return (NULL);
	result = search_in_path(cmd, dirs);
	free_args(dirs);
	return (result);
}
