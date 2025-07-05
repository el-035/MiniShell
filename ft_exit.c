#include "minishell.h"

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
	char	*clean;
	int		sign;

	sign = 0;
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
	if (ft_strncmp(converted, clean, ft_strlen(converted)) != 0) // vehck thias
		return (free(converted), free(clean), -1);
	return (free(converted), free(clean), 1);
}

void	print_err(char *str, int flag)
{
	if (flag == 1)
	{
		write(2, "bash: exit: ", 12);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		return_exit_code(2);
	}
	else if (flag == 2)
	{
		write(2, "exit: too many arguments\n", 25);
		return_exit_code(1);
	}
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
			return (fail_mall(), free_split(data->envp), free_all(data),
				exit(1));
		is_valid = check_overflow(trimmed);
		if (is_valid == -2)
			return (free_split(data->envp), free_all(data), exit(1));
		if (ft_str_digit(trimmed) != 0 || is_valid == -1)
			print_err(cmd->args[1], 1);
		else if (cmd->args[2] && ft_str_digit(cmd->args[1]) == 0)
			print_err(cmd->args[1], 2);
		else
			error_n(cmd->args[1]);
		free(trimmed);
		return (free_split(data->envp), free_all(data), exit(return_exit_code(-2)));
	}
	return (free_split(data->envp), free_all(data), exit(return_exit_code(-1)));
}
