/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:22:04 by efittant          #+#    #+#             */
/*   Updated: 2025/07/09 19:30:59 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 0;
	if (!ft_strchr(str, '='))
		return (ft_strdup(str));
	while (str[i] != '=' && str[i] != '+')
		i++;
	var = ft_calloc(i + 1, sizeof(char));
	if (!var)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '+')
	{
		var[i] = str[i];
		i++;
	}
	return (var);
}

char	*get_content(char *str)
{
	int		i;
	int		len;
	char	*conetnt;

	if (!ft_strchr(str, '='))
		return (NULL);
	len = ft_strlen(ft_strchr(str, '=') + 1);
	conetnt = ft_calloc(len + 1, sizeof(char));
	if (!conetnt)
		return (fail_mall(), NULL);
	str = ft_strchr(str, '=') + 1;
	i = -1;
	while (str[++i])
		conetnt[i] = str[i];
	return (conetnt);
}

char	**copy(char **envp, t_data *data)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = ft_calloc(data->envp_size + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
			i++;
		if (envp[i])
			cpy[j++] = ft_strdup(envp[i++]);
		if (!cpy[j - 1])
			return (free_split(cpy), NULL);
	}
	return (cpy);
}

void	sort(char **cpy)
{
	int		flag;
	char	*tmp;
	int		i;

	flag = 1;
	i = 0;
	while (flag != 0)
	{
		flag = 0;
		i = 0;
		while (cpy[i] && cpy[i + 1])
		{
			if (ft_strncmp(cpy[i], cpy[i + 1], ft_strlen(cpy[i])) > 0)
			{
				tmp = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp;
				flag = 1;
			}
			i++;
		}
	}
}

void	actual_print(char *var,char *content)
{
	write(1, "declare -x ", 11);
	ft_putstr_fd(var, 1);
	write(1, "=\"", 2);
	ft_putstr_fd(content, 1);
	write(1, "\"\n", 2);
}

int	print_export(char **envp, t_data *data)
{
	char	**cpy;
	int		i;
	char	*var;
	char	*content;

	i = 0;
	cpy = copy(envp, data);
	if (!cpy)
		return (fail_mall(), 1);
	sort(cpy);
	while (cpy[i])
	{
		var = get_var(cpy[i]);
		if (!var)
			return (fail_mall(), free_split(cpy), 1);
		content = get_content(cpy[i]);
		if (!content)
			return ((free_split(cpy), free(var), fail_mall(), 1));
		actual_print(var, content);
		free(var);
		free(content);
		i++;
	}
	return (free_split(cpy), 0);
}
