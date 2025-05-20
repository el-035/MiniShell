#include "minishell.h"

void	*ft_echo(t_cmd *cmd)
{
	int	i;
	int nl;

	nl = 1;
	i = 1;
	if (!cmd->args[i])
		return (printf("\n"), NULL);
	else if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while(cmd->args[i])
	{
		printf ("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
	return (NULL);
}

void	ft_exit(t_data *data/* , t_cmd *cmd */)
{
	/* FREE DATA AND CMD */
	free_all(data);
	exit(return_exit_code(-1));	//or 1
}