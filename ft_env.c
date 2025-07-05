#include "minishell.h"

void	ft_env(char **env)
{
	int	i;
	//char *tmp;

	i = -1;
	signal(SIGPIPE, SIG_IGN);
	while (env[++i])
		printf("%s\n", env[i]);
	/* {
		tmp = ft_strdup(env[i]);
			//protect;
		remove_useless_quotes(&tmp, ft_strlen(tmp));
		printf("%s\n", tmp);
		free(tmp);
	} */
}
