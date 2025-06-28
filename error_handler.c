#include "minishell.h"

void	handle_error(char *str, int error_code)
{
	if (error_code == 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": No such file or directory\n", 28);
	//	return_exit_code(1);
	}
	else if (error_code == 1)
	{
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 20);
	//	return_exit_code(1);
	}
	else if (error_code == 2)
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
	}
}
