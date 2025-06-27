#include "minishell.h"

void	update_envp(char **envp, char *var, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!envp[i])
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			tmp = ft_strjoin(var, value);
			if (!tmp)
				return (fail_mall());
			free(envp[i]);
			envp[i] = tmp;
			return ;
		}
		i++;
	}
}

void	cd_helper(t_cmd *cmd, t_data *data)
{
	char	*home;

	if (!cmd->args[1] || cmd->args[1][0] == '\0')
	{
		home = extract_var(data->envp, ft_strdup("HOME"));
		if (!home)
			fail_mall();
		if (home[0] == '\0')
		{
			write (2, "bash: cd: HOME not set\n", 23);
			return_exit_code(1);
		}
		remove_useless_quotes(&home, return_final_len(home));
		if (chdir(home) == -1)
			return_exit_code(1);
		free(home);
	}
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
		write(2, "getcwd failed\n", 15);
	cd_helper(cmd, data);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		write(2, "getcwd failed\n", 15);
	update_envp(data->envp, "OLDPWD=", old_pwd);
	update_envp(data->envp, "PWD=", new_pwd);
	free(old_pwd);
	free(new_pwd);
}
