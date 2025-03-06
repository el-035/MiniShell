#include"minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;

	while (1)
	{
		line = readline("Minishell: ");
		if (strncmp(line, "exit", 5) == 0)
			break ;
		free(line);
	}
}