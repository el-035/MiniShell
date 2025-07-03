#include "minishell.h"

int	unquoted_var(char *content)
{
	int i = 0;

	if (!content || content[0] == '\0')
		return -1;
	while(content[i])
	{
		if (content[i] == '$')
		{
			if (!content[i + 1])
				return -1;
			if (check_quotes(content, i) == 0 && (ft_isalpha(content[i + 1]) || content[i + 1] == '_'))
				return (i);
		}
		i++;
	}
	return -1;
}

char *save_unquoted_start(char *content, int i, char **env)
{
	char *start;

	int	j;

	j = 0;
	if (i == 0)
		return (ft_strdup(""));
	start = ft_calloc(i + 1, sizeof(char));
	if (!start)
		return NULL; //protect
	while (j < i)
	{
		start[j] = content[j];
		j++;
	}
	if (stop(start) != 0)
		expand_var(&start, env);
	return (start);
}

//first check if there is unquoted var
	//no -> just use wjaz o had and go on
	//yes -> save everything untill unquoted var
		// save first token of unquoted var
		//this is the current token
		//save everything and pass it as content to new token
			//start again
t_input	*add_node(t_input *cur, char *content)
{
	t_input	*new;

	//protect content
	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_input));
	init_input(new);
	new->content = ft_strdup(content);
    if (!new->content)
    {
        free(new);
        return (NULL);
    }
	cur->next->prev = new;
	new->next = cur->next;
	new->prev = cur;
	cur->next = new;

	return (new);
}
t_input *beginning(t_input *cur, char *start, char *exp, int f_b)
{
	if (start && start[0] != '\0')
	{
		if (f_b == 1)
		{
			cur->content = ft_strdup(start);
			cur = add_node(cur, exp);
			cur->exp = 0;
		}
		else
		{
			cur->content = ft_strjoin(start, exp);
			cur->exp = ft_strlen(start);
		}
	}
	else
	{
		cur->content = ft_strdup(exp);
		cur->exp = 0;
	}
	return (cur);
}

t_input *end(t_input *cur, char *next, int f_e)
{
	char *tmp;

	if (next && next[0] != '\0')
	{
		if (f_e == 1)
		{
			cur = add_node(cur, ft_strdup(next));
		}
		else
		{
			tmp = cur->content;
			cur->content = ft_strjoin(tmp, next);
			cur->exp = 0 - ft_strlen(tmp);
			free(tmp);
		}
	}
	return (cur);
}
t_input *middle(t_input *cur, char **split)
{
	int len = arr_len(split);
	int i = 1;
	while (i < len - 1)
	{
		cur = add_node(cur, split[i++]);
		if (!cur)
            return (NULL);
		cur->exp = 0;
	}
	return (cur);
}

t_input *new_token(t_input *cur, char *start, char *exp, char *next)
{
	int count;
	char **split;
	int len;
	int	f_b;
	int f_e;

	count = count_word(exp);
	f_b = is_space(exp[0]);
	f_e = is_space(exp[ft_strlen(exp) - 1]);
	if (exp[0] == '\0')
	{
		cur->content = ft_strjoin(start, next);	//protect
		return cur;
	}
	else if (count == 0)
	{
		cur->content = start;
		cur = add_node(cur, next);
	}
	split = space_split(exp);
	if (!split)
		return (NULL);
	else if (count == 1)	//
	{
		cur = beginning(cur, start, split[0], f_b);
		cur = end(cur, next, f_e);
	}
	else if (count > 1)
	{
		len = arr_len(split);
		cur = beginning(cur, start, split[0], f_b);
		if (!cur)
        {
            free_split(split);
            return (NULL);
        }
		if (len > 2)
        {
            cur = middle(cur, split);
            if (!cur)
            {
                free_split(split);
                return (NULL);
            }
        }
		cur = add_node(cur, ft_strdup(split[len - 1]));
		cur->exp = 0;
		cur = end(cur, next, f_e);
	}
	return (free_split(split), cur);
}

int	exp_tokenise(t_input *cur, char **envp)
{
	char *start;
	char *var;
	char *exp; 
	char *next;
	int	pos;

	pos = unquoted_var(cur->content);
	if (pos == -1)
		return (expand_var(&(cur->content), envp));
	start = save_unquoted_start(cur->content, pos, envp);
	//protect
	var = save_var(&(cur->content[pos]));

	if (!var)
		return -1; //proewr
	next = save_rest(&(cur->content[pos + 1]), var);		//eehmm 
	//prttetctw6azuhv;

	exp = extract_var(envp, var);

	if (!exp)
		return -1; //proewr
	free(cur->content);
	cur->content = NULL;
	new_token(cur, start, exp, next);

	if (unquoted_var(cur->content) != -1)
		exp_tokenise(cur, envp);
	
	return 0;
}
