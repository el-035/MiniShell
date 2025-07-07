/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:03:10 by efittant          #+#    #+#             */
/*   Updated: 2025/07/07 19:31:29 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_join(char *s1, char *s2, char *s3)
{
	char	*final;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (len == 0)
		return (ft_strdup(""));
	final = (char *) ft_calloc(len + 1, sizeof(char));
	if (!final)
		return (NULL);
	while (s1 && s1[i] && j < len)
		final[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] && j < len)
		final[j++] = s2[i++];
	i = 0;
	while (s3 && s3[i] && j < len)
		final[j++] = s3[i++];
	return (final);
}

int	expand_var_hd(char **content, char **envp)
{
	char	*start;
	char	*var;
	char	*end;

	if (stop(*content) == 0)
		return (0);
	start = save_start(*content);
	if (!start)
		return (-1);
	var = save_var(&(*content)[start_len(*content)]);
	if (!var)
		return (free(start), -1);
	end = save_rest(search_var(*content, var) + 1, var);
	if (!end)
		return (free(start), free(var), -1);
	var = extract_var(envp, var);
	if (!var)
		return (free(start), free(end), -1);
	if (join_all(content, start, end, var) == 1)
		return (-1);
	if (ft_strchr(*content, '$') != 0)
		expand_var(content, envp);
	return (0);
}

int	count_quoted_var(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (content[0] == '\0')
		return (0);
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (!content[i + 1])
				return (count);
			if (check_quotes(content, i) == 2 && (ft_isalpha(content[i + 1])
					|| content[i + 1] == '_'))
				count++;
		}
		i++;
	}
	return (count);
}

int	find_var(char **envp, char *str)
{
	char	*var;
	int		len;
	int		i;

	i = 0;
	var = ft_strjoin(str, "=");
	if (!var)
		return (fail_mall(), -2);
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (free(var), i);
		i++;
	}
	free(var);
	return (-1);
}
