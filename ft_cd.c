#include "minishell.h"

int	update_envp(t_data *data, char *var, char *value)
{
	int		i;
	char	*tmp;

	if (!data->envp[0])
		return (0);
	i = find_var(data->envp, var);
	if (i == -1)
	{
		if (add_env(data, var, value) != 0)
			return(fail_mall(), -1);
		else
			return (0);
	}
	else if (i == -2)
		return (-1);
	tmp = double_join(var, "=", value);
	if (!tmp)
		return (fail_mall(), -1);
	free(data->envp[i]);
	data->envp[i] = tmp;
	return (0);
}

void	cd_more_help(t_cmd *cmd, t_data *data)
{
	char	*home;

	home = extract_var(data->envp, ft_strdup("HOME"));
	if (!home)
		return (fail_mall());
	if (home[0] == '\0')
	{
		write(2, "bash: cd: HOME not set\n", 23);
		return (return_exit_code(1), free(home));
	}
	if (cmd->args[1] && cmd->args[1][0] == '\0')
		return ;
	if (chdir(home) == -1)
		return_exit_code(1);
	free(home);
}

void	cd_helper(t_cmd *cmd, t_data *data)
{
	if (!cmd->args[1] || cmd->args[1][0] == '\0')
		cd_more_help(cmd, data);
	else if (cmd->args[2])
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return_exit_code(1);
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		write(2, "cd: ", 4);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": No such file or directory\n", 28);
		return_exit_code(1);
	}
}

void	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		write(2, "getcwd failed: OLD_PWD could not be retrtived\n", 46);
	cd_helper(cmd, data);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		write(2, "getcwd failed: PWD could not be retrtived\n", 42);
	if (update_envp(data, "OLDPWD", old_pwd) != 0)
		return (free(old_pwd), free(new_pwd));
	if (update_envp(data, "PWD", new_pwd))
		return (free(old_pwd), free(new_pwd));
	free(old_pwd);
	free(new_pwd);
}
