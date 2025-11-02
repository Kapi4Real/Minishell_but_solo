#include <minishell.h>

void	add_arg_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_args;
	int		i;

	if (!cmd || !arg)
		return ;
	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}
