#include "minishell.h"

char *beg(char *content)
{
	int len;
	int	i;
	char *beg;

	len = 0;
	i = 0;
	
	while (content[len])
	{
		if (content[len] == '$')
			if (content[len + 1] && (content[len + 1] == '?'))
				break ;
		len++;
	}
	if (len == 0)
		return (ft_strdup(""));
	beg = (char *) ft_calloc((len + 1), sizeof(char));
	if (!beg)
		return (printf("Allocation failed\n"), NULL); //
	while(i < len)
	{
		beg[i] = content[i];
		i++;
	}
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

int	expand_exit(t_input **cur, t_data *data)
{
	char *start;
	char *var;
	char	*end;

	start = beg((*cur)->content);
	if (!start)
		return (1);
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

int	find_exit(t_input *first, t_data *data)
{
	t_input	*cur;

	cur = first;
	while(cur)
	{
		if (ft_strnstr(cur->content, "$?", ft_strlen(cur->content)))
			expand_exit(&cur, data);
		cur = cur->next;
		if (cur == first)
			break ;
	}
	return 0;
}