#include "minishell.h"

int	valid_opt(char *opt)
{
	int	i;

	i = 1;
	if (opt[0] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	nl = 1;
	i = 1;
	signal(SIGPIPE, SIG_IGN);
	if (!cmd->args[i])
	{
		printf("\n");
		return ;
	}
	else if (valid_opt(cmd->args[i]) == 1)
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
