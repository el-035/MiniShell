#include "minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	signal(SIGPIPE, SIG_IGN);
	while (env[++i])
		printf("%s\n", env[i]);
}
