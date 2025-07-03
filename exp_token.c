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

t_input *new_token(t_input *cur, char *start, char *exp, char *next)
{
	int count;
	t_input *new;
	char *tmp;
	
	new = NULL;
	count = count_word(exp);
	if (exp[0] == '\0')
	{
		//printf("1\n");
		tmp = ft_strjoin(start, next);
		//iohfekujbva
		/* //printf("cur: %s\ntmp: %s\n", cur->content, tmp); */
		//free(cur->content); /* free(start); free(next);	 */	//chechiekhoifhwoiusv
		cur->content = tmp;
		return (NULL);
	}
	else if (count == 1)	//
	{
		//printf("2\n");
		if ((!start || start[0] == '\0') && (!next || next[0] == '\0'))
		{
			cur->content = ft_strdup(exp);
			return NULL;
		}
		//protect and free exerehg
		if (is_space(exp[ft_strlen(exp) - 1]) != 1 && is_space(exp[0]) != 1)
		{
			cur->content = double_join(start, exp, next);
			return NULL;
		}
	}
	else if (count >= 1)
	{
		//printf("3\n");
		ft(cur, exp, next, start);

	}
	return (new);
}
	
int	exp_tokenise(t_input *cur, char **envp)
{
	char *start;
	char *var;
	char *exp; 
	char *next;
	int	pos;

	pos = unquoted_var(cur->content);
	////printf("%d\n", pos);
	//printf("content: %s\n", cur->content);
	if (pos == -1)
		return (expand_var(&(cur->content), envp));
	start = save_unquoted_start(cur->content, pos, envp);
	//printf("start: %s\n", start);
	//protect
	var = save_var(&(cur->content[pos]));
	//printf("var: %s\n", var);
	if (!var)
		return -1; //proewr
	next = save_rest(&(cur->content[pos + 1]), var);		//eehmm 
	//prttetctw6azuhv;
	//printf("next: %s\n", next);
	exp = extract_var(envp, var);
	//printf("exp: %s\n", exp);
	if (!exp)
		return -1; //proewr
	/* new = */ new_token(cur, start, exp, next);
//printf("content %s\n", cur->content);
	//proetct
//	free(var);
//	free(next);
	/* free(start); free(var); free(exp); free(next); */
	if (unquoted_var(cur->content) != -1)
		exp_tokenise(cur, envp);
	
	return 0;
}
