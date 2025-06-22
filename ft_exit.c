#include "minishell.h"
#include <limits.h>

long	long_atoi(const char *str)
{
	int	i;
	long	result;
	int	n;

	n = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(&str[i], "-9223372036854775808", 20) == 0)
		return (LONG_MIN);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	if (str[i])
	{
		while (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + str[i++] - 48;
	}
	return (result * n);
}

int	error_n(char *err)
{
	int	n;

	n = ft_atoi(err);
	while (n < 0)
		n += 256;
	while (n > 255)
		n -= 256;
	return (return_exit_code(n));
}

char	*clean_input(char *trim)
{
	char	*tmp;
	char	*clean;
	int		sign;

	sign = 0;
	tmp = trim;
	if (*trim == '+' || *trim == '-')
	{
		sign = *trim;
		trim++;
	}
	while (*trim == '0' && trim[1] != '\0')
		trim++;
	if (sign == '-')
		clean = ft_strjoin("-", trim);
	else	
		clean = ft_strdup(trim);
	if (!clean)
		return (free(tmp), NULL);
	return (free(tmp), clean);
}
int		check_overflow(char *input, char *trimmed)
{
	char *converted;
	char *clean;

	converted = ft_itoa(long_atoi(input));
		//protect
	clean = clean_input(trimmed);
		//protect
	if (ft_strncmp(converted, clean, ft_strlen(converted)) != 0)
		return (free(converted), free(clean), -1);
	return (free(converted), free(clean), 1);
}

void	ft_exit(t_data *data, t_cmd *cmd)
{
	char *trimmed;

	printf("exit\n");
	if (cmd->args[1])
	{
		trimmed = ft_strtrim(cmd->args[1], " \t");
		if (ft_str_digit(trimmed) != 0 || check_overflow(cmd->args[1], trimmed) == -1)
		{
			write(2, "bash: ", 6);
			write(2, "exit: ", 6);
			write(2, cmd->args[1], ft_strlen(cmd->args[1]));
			write(2, ": numeric argument required\n", 28);
			return_exit_code(2);
		}
		else if (cmd->args[2] && ft_str_digit(cmd->args[1]) == 0)
		{
			write(2, "exit: too many arguments\n", 25);
			return_exit_code(1);
		} 
		else
			error_n(cmd->args[1]);
	}
	free_split(data->envp);
	free_all(data);
	exit(return_exit_code(-2)); // or 1
}
