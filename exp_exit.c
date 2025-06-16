#include "minishell.h"

char *beg(char *content)
{
	int len;
	int	i;
	char *beg;

	len = 0;
	i = -1;
	while (content[len])
	{
		if (content[len] == '$')
			if (content[len + 1] && (content[len + 1] == '?') && check_quotes(content, len) != 1)
				break ;
		len++;
	}
	if (len == 0)
		return (ft_strdup(""));
	beg = (char *) ft_calloc((len + 1), sizeof(char));
	if (!beg)
		return (printf("Allocation failed\n"), NULL); //
	while(++i < len)
		beg[i] = content[i];
	return (beg);
}

char *save_end(char *content, int len)
{
	char	*end;
	int		i;

	i = 0;
	while (content[len + i])
		i++;
	end = (char *) ft_calloc((i + 1), sizeof(char));
	if (!end)
		return (printf("Allocation failed\n"), NULL); //
	i = 0;
	while(content[len])
	{
		end[i] = content[len];
		i++;
		len++;
	}
	return (end);
}

int	no_more(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] && (content[i + 1] == '?') && check_quotes(content, i) == 1)
				i += 2;
			else if (!content[i + 1])
				return 0;
			else
				return (1);
		}
		else
			i++;
	}
	return 0;
}

int	expand_exit(t_input **cur, t_data *data)
{
	char *start;
	char *var;
	char	*end;

	if (no_more((*cur)->content) == 0)
		return 0;
	start = beg((*cur)->content);
	if (!start)
		return (1);
	if (return_sig_flag(-1) != 0)
	{
		var = ft_strdup(ft_itoa(130));
		return_sig_flag(0);
	}
	else
		var = ft_strdup(ft_itoa(return_exit_code(-1)));
	if (!var)
		return (free(start), 1);
	end = save_end((*cur)->content, ft_strlen(start) + 2);
	if (!end)
		return (free(start), free(var), 1);
	if (join_all(cur, start, end, var) == 1)
		return 1;	//error or wat ?
	if (ft_strnstr((*cur)->content, "$?", ft_strlen((*cur)->content)))
	 	expand_exit(cur, data);
	return 0;
}