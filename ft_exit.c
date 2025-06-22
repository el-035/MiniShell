#include "minishell.h"
#include <limits.h>

long	long_atoi(const char *str)
{
	int		i;
	long	result;
	int		n;

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

	n = long_atoi(err);
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
	return (clean);
}
int	check_overflow(char *trimmed)
{
	char	*converted;
	char	*clean;


	clean = clean_input(trimmed);
	if (!clean)
		return (fail_mall(), free(trimmed), -2);


	converted = ft_itoa(long_atoi(clean));
	if (!converted)
		return (fail_mall(), free(trimmed), free(clean), -2);


	if (ft_strncmp(converted, clean, ft_strlen(converted)) != 0)		//vehck thias
		return (free(converted), free(clean), -1);
	return (free(converted), free(clean), 1);
}

void	ft_exit(t_data *data, t_cmd *cmd)
{
	char	*trimmed;
	int		is_valid;

	printf("exit\n");
	if (cmd->args[1])
	{
		trimmed = ft_strtrim(cmd->args[1], " \t");
		if (!trimmed)
			return (fail_mall(), free_split(data->envp), free_all(data), exit(1));
		
		is_valid = check_overflow(trimmed);
		if (is_valid == -2)
			return (free_split(data->envp), free_all(data), exit(1));


		if (ft_str_digit(trimmed) != 0 || is_valid == -1)
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
		free (trimmed);
	}
	return (free_split(data->envp), free_all(data), exit(return_exit_code(-2)));
}
