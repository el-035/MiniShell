#include "minishell.h"

void	exec_builtin_child(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(data->envp);
}

int	exec_builtin_parent(t_cmd *cmd, t_data *data)
{
	// Maybe use exit_code to set EC immediately?
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(data, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(data, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(data, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(data, cmd);
	else
		return (1);
	return (0);
}
