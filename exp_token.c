#include "minishell.h"

int	unquoted_var(char *content)
{
	int	i;

	i = 0;
	if (!*content || !content || content[0] == '\0')
		return (-1);
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (!content[i + 1])
				return (-1);
			if (check_quotes(content, i) == 0 && (ft_isalpha(content[i + 1])
					|| content[i + 1] == '_'))
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*save_unquoted_start(char *content, int i, char **env)
{
	char	*start;
	int		j;

	j = 0;
	if (i == 0)
		return (ft_strdup(""));
	start = ft_calloc(i + 1, sizeof(char));
	if (!start)
		return (fail_mall(), NULL); // protect
	while (j < i)
	{
		start[j] = content[j];
		j++;
	}
	if (stop(start) != 0)
		expand_var(&start, env);
	return (start);
}

t_input	*new_token(t_input *cur, char *start, char *exp, char *next)
{
	char	**split;

	free(cur->content);
	cur->content = NULL;
	if (exp[0] == '\0' || count_word(exp) == 0)
		return (empty(cur, start, next, exp));
	split = space_split(exp);
	if (!split)
		return (NULL);
	if (count_word(exp) >= 1)
	{
		cur = beginning(cur, start, split[0], is_space(exp[0]));
		if (!cur)
			return (free_split(split), NULL);
		cur = middle(cur, split);
		if (!cur)
			return (free_split(split), NULL);
		cur = end(cur, next, is_space(exp[ft_strlen(exp) - 1]));
		if (!cur)
			return (free_split(split), NULL);
		if (count_word(exp) == 1)
			cur->exp = INT_MAX;
	}
	return (free_split(split), cur);
}

int	exp_tokenise(t_input *cur, char **envp)
{
	char	*start;
	char	*var;
	char	*exp;
	char	*next;

	if (unquoted_var(cur->content) == -1)
		return (expand_var(&(cur->content), envp));
	start = save_unquoted_start(cur->content, unquoted_var(cur->content), envp);
	if (!start)
		return (-1);
	var = save_var(&(cur->content[unquoted_var(cur->content)]));
	if (!var)
		return (free(start), -1);
	next = save_rest(&(cur->content[unquoted_var(cur->content) + 1]), var);
	// eehmm
	if (!next)
		return (free(start), free(var), -1);
	exp = extract_var(envp, var);
	if (!exp)
		return (free(start), free(var), free(next), -1);
	new_token(cur, start, exp, next);
	if (unquoted_var(cur->content) != -1)
		exp_tokenise(cur, envp);
	return (free(start), free(next), free(exp), 0);
}
