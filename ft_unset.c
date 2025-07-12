/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:33:08 by efittant          #+#    #+#             */
/*   Updated: 2025/07/12 01:42:15 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	var_count(char **envp, char **args)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (!envp || !*envp)
		return (-1);
	while (envp[i])
	{
		j = 1;
		while (args[j])
		{
			if (ft_strncmp(envp[i], args[j], ft_strlen(args[j])) == 0
				&& (envp[i][ft_strlen(args[j])] == '='
				|| envp[i][ft_strlen(args[j])] == '\0'))
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

int	copy_var(char *envp, char **var)
{
	int	i;
	int	len;

	i = 1;
	while (var[i])
	{
		len = ft_strlen(var[i]);
		if (ft_strncmp(envp, var[i], ft_strlen(var[i])) == 0
			&& (envp[len] == '=' || envp[len] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	char	**tmp;

	if (!cmd->args[1])
		return (1);
	i = var_count(data->envp, cmd->args);
	if (i == 0)
		return (1);
	tmp = ft_calloc((data->envp_size - i) + 1, sizeof(char *));
	if (!tmp)
		return (fail_mall(), 0);
	data->envp_size -= i;
	i = 0;
	j = 0;
	while (data->envp[i])
	{
		if (copy_var(data->envp[i], cmd->args) == 1)
			tmp[j++] = data->envp[i];
		else
			free(data->envp[i]);
		i++;
	}
	return (free(data->envp), data->envp = tmp, 1);
}
