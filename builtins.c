#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int nl;

	nl = 1;
	i = 1;
	if (!cmd->args[i])
	{
		printf("\n");
		return ;
	}
	else if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while(cmd->args[i])
	{
		printf ("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl == 1)
		printf("\n");
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

void	ft_exit(t_data *data, t_cmd *cmd)
{
	printf("exit\n");		//i think it should be there but the tester doesnt like it
	if (cmd->args[1])
	{		
		if (ft_str_digit(cmd->args[1]) != 0)
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
	exit(return_exit_code(-2));	//or 1
}


void	update_envp(char **envp, char *var, char *value)
{
	int i;

	i = 0;
	if (!envp[i])
		return ;	//erioror
	while(envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strjoin(var, value);
			if (!envp[i])
				return; //eroor
			return ;
		}
		i++;
	}
}

void	ft_cd(t_data *data, t_cmd *cmd)		//handle -
{
	char *old_pwd;
	char *new_pwd;
	char *home;


	old_pwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		home = extract_var(data->envp, ft_strdup("HOME"));
		if (chdir(home) == -1)
		{
			return_exit_code(1);
		}
		free(home);
	}
	else if (cmd->args[2])
	{
		write(2, "bash: ", 6);
		write(2, "cd: ", 4);
		//write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, "too many arguments\n", 19);
		return_exit_code(1);
	}
	else /* (cmd->args[1]) */
	{
		if(chdir(cmd->args[1]) == -1)
		{
			write(2, "cd: ", 4);
			write(2, cmd->args[1], ft_strlen(cmd->args[1]));
			write(2, ": No such file or directory\n", 28);
			return_exit_code(1);
		}
	}
	new_pwd = getcwd(NULL, 0);
	update_envp(data->envp, "OLDPWD=", old_pwd);
	update_envp(data->envp, "PWD=", new_pwd);
	free(old_pwd);
	free(new_pwd);
}

int arr_len(char **arr)
{
	int i;

	i = 0;
	
	if (!arr)
		return 0;
	while(arr[i])
		i++;
	return i;
}

int		var_count(char **envp, char **args)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
/* 	if (!envp || !*envp)
		return -1; */
	while (envp[i])
	{
		j = 1;
		while (args[j])
		{
			if (ft_strncmp(envp[i], args[j], ft_strlen(args[j])) == 0 && envp[i][ft_strlen(args[j])] == '=')
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int		copy_var(char *envp, char **var)
{
	int i;

	i = 1;
	while (var[i])
	{
		if (ft_strncmp(envp, var[i], ft_strlen(var[i])) == 0 && (envp[ft_strlen(var[i])] == '='))
			return 0;
		i++;
	}
	return (1);
}

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int i;
	int j;
	char **tmp;

	if (!cmd->args[1])
		return ;
	i = var_count(data->envp, cmd->args);
	if (i == 0)
		return ; //var not found
	tmp = ft_calloc((arr_len(data->envp) - i) + 1, sizeof(char *));
	if (!tmp)
		return ; //errorr
	i = 0;
	j = 0;
	while(data->envp[i])
	{
		if (copy_var(data->envp[i], cmd->args) == 1)
			tmp[j++] =  ft_strdup(data->envp[i]);	//protect
		i++;
	}
	free_split(data->envp);
	data->envp = tmp;
}
