#include "minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)		//crtl C
	{
		printf("\n");
		exit(SIGINT + 128);
	}
	if (sig == SIGQUIT)		//ctrl /
		exit(SIGQUIT + 128);
}
