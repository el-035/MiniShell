#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	signal(SIGPIPE, SIG_IGN);
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd: ");
}
