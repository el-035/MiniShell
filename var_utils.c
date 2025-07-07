#include "minishell.h"

char	*search_var(char *content, char *var)
{
	char	*temp;
	int		len;
	char	*full_var;
	int		full_len;

	len = ft_strlen(content);
	temp = content;
	full_var = ft_strjoin("$", var);
	if (!full_var)
		return (NULL); // hehe
	full_len = ft_strlen(full_var);
	while (temp - content <= len)
	{
		temp = ft_strnstr(temp, full_var, full_len);
		if (check_quotes(content, temp - content) != 1)
			break ;
		temp++;
	}
	free(full_var);
	return (temp);
}

int	stop(char *content)
{
	int	i;

	i = 0;
	if (!content)
		return (0);
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '$'))
				i += 2;
			else if (content[i + 1] && !(ft_isalpha(content[i + 1]) || content
					[i + 1] == '_'))
				i++;
			else if (check_quotes(content, i) == 1)
				i++;
			else if (!content[i + 1])
				return (0);
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	*extract_var(char **envp, char *var) //
{
	char	*value;
	char	*temp;
	char	*full;
	int		i;
	int		len;

	i = 0;
	if (!var || !*var)
		return (free(var), ft_strdup(""));
	full = ft_strjoin(var, "=");
	if (!full)
		return (free(var), NULL);
	len = ft_strlen(full);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], full, len) == 0)
		{
			temp = ft_strchr(envp[i], '=') + 1;
			value = ft_strdup(temp);
			return (free(var), free(full), value);
		}
		i++;
	}
	return (free(var), free(full), ft_strdup(""));
}

char	*save_var(char *content) //
{
	int		i;
	int		len;
	char	*var;

	i = -1;
	len = 0;
	if (!content || !*content)
		return (NULL);
	if (content[1])
		content++;
	while (content[len])
	{
		if (ft_isalnum(content[len]) || content[len] == '_')
			len++;
		else
			break ;
	}
	var = (char *)ft_calloc((len + 1), sizeof(char));
	if (!var)
		return (NULL);
	while (++i < len)
		var[i] = content[i];
	return (var);
}

int	start_len(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '$'))
				i += 2;
			else if (content[i + 1] && !(ft_isalnum(content[i + 1]) || content
					[i + 1] == '_'))
				i++;
			else if (check_quotes(content, i) == 1)
				i++;
			else
				return (i);
		}
		else
			i++;
	}
	return (i);
}
