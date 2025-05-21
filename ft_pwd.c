#include "minishell.h"

void ft_pwd()
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd: ");
}
