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
	free_all(data);
	exit(return_exit_code(-1));	//or 1
}
/* calling getcwd to later  store what OLDPWD in envp contains
if cd with no arg call chdir with looking for  $HOME in envp
if cd with path call chdir with input
if chdir fails because the path specified does not exist perror or strerror

then  updating pwd  */
#include <stdio.h>
#include <string.h>

/* void print_pwd_oldpwd(char **envp)
{
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
		printf("WTF\n");	//erioror
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
			handle_error(cmd->args[1], 1); 		//not sure what number
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
	print_pwd_oldpwd(data->envp);
}
