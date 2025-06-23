#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	nl = 1;
	i = 1;
	if (!cmd->args[i])
	{
		printf("\n");
		return ;
	}
	else if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
}
