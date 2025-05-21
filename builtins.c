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

void	ft_exit(t_data *data/* , t_cmd *cmd */)
{
	/* FREE DATA AND CMD */
	free_split(data->envp);
	free_all(data);
	exit(return_exit_code(-1));	//or 1
}

/* void print_pwd_oldpwd(char **envp)
{
	#include <stdio.h>
	#include <string.h>
    int i = 0;

    while (envp[i])
    {
        if (strncmp(envp[i], "PWD=", 4) == 0 || strncmp(envp[i], "OLDPWD=", 7) == 0)
            printf("%s\n", envp[i]);
        i++;
    }
} */

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

void	ft_cd(t_data *data, t_cmd *cmd)
{
	char *old_pwd;
	char *new_pwd;
	char *home;

	old_pwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		home = extract_var(data->envp, ft_strdup("HOME"));
		if (chdir(home) == -1)
			handle_error(cmd->args[1], 2); 		//not sure what number
		free(home);
	}
	else if (cmd->args[1])
	{
		if(chdir(cmd->args[1]) == -1)
			handle_error(cmd->args[1], 1); 		//not sure what number
	}
	new_pwd = getcwd(NULL, 0);
	update_envp(data->envp, "OLDPWD=", old_pwd);
	update_envp(data->envp, "PWD=", new_pwd);
	free(old_pwd);
	free(new_pwd);
	//print_pwd_oldpwd(data->envp);
}

void print_unset(char **envp)
{
	#include <stdio.h>
	#include <string.h>
    int i = 0;

    while (envp[i])
    {
        if (strncmp(envp[i], "PWD=", 4) == 0 || strncmp(envp[i], "OLDPWD=", 7) == 0)
            printf("%s\n", envp[i]);
        i++;
    }
} 

void	ft_unset(t_data *data, t_cmd *cmd)
{
	int i;

	i = 0;
	print_unset(data->envp);
	printf("unset starting\n");
	if (!cmd->args[1])
		return ;		//unset: not enough arguments on strerr + exit code 1
	while(data->envp[i])
	{
		if (ft_strncmp(data->envp[i], cmd->args[1], ft_strlen(cmd->args[1])) == 0)
			break ;
		i++;
	}
	//need to add a check if var is not found
	if (!data->envp[i + 1])
		return ;
	while(data->envp[i])
	{
		free(data->envp[i]);
		if (data->envp[i + 1])
			data->envp[i] = ft_strdup(data->envp[i + 1]);
		i++;
	}
	printf("unset done\n");
	print_unset(data->envp);

}