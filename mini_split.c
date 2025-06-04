#include "minishell.h"

static int is_delimitor(char c)
{
	if (c == 32 || c == 9)
		return 1;
	else if (c == 124 || c == 60 || c == 62)
		return 2;
	return 0;
}

static int	ft_word_count(char *s)
{
	int	i;
	int	wc;
	char	c;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (is_delimitor(s[i]) != 0)
		{
			if (is_delimitor(s[i]) == 2)
			{
				c = s[i];
				while (s[i] == c)
					i++;
				wc++;
			}
			i++;
		}
		if (!s[i])
			break ;
		wc++;
		while (s[i])
		{
			if (is_delimitor(s[i]) != 0 && check_quotes(s, i) == 0)
				break ;
			i++;
		}
	}
	return (wc);
}

static int word_len(char *s, int i)
{
	int		j;
	int		flag;

	j = i;
	flag = -1;
	while ((s[i] == 32 || s[i] == 9))
		i++;
	if (!s[i])
		return 0;
	if (is_delimitor(s[i]) == 2)
		flag = s[i];
	while(s[i])
	{
		if (is_delimitor(s[i]) != 0 && check_quotes(s, i) == 0)
		{
			while(s[i] == flag)
				i++;
			break ;
		}
		i++;
	}
	return (i - j);
}

static char	*ft_word(char *s, int i)
{
	char	*word;
	int		j;
	int		len;

	while ((s[i] == 32 || s[i] == 9) && s[i])
		i++;
	len = word_len(s, i);
	word = (char *) ft_calloc((len + 1), sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
		word[j++] = s[i++];
	return (word);
}

char	**mini_split(char const *s)
{
	int		wc;
	int		i;
	int		j;
	char	**split;

	wc = ft_word_count((char *) s);
	if (!wc)
		return (NULL);
	i = 0;
	j = 0;
	split = (char **) ft_calloc ((wc + 1), sizeof(char *));
	if (!split)
		return (NULL);
	while (s && split && j < wc)
	{
		split[j] = ft_word((char *)s, i);
		if (!split[j++])
			return (free_split(split), NULL);
		while ((s[i] == 32 || s[i] == 9) && s[i])
			i++;
		i = i + ft_strlen(split[j - 1]);
	}
	split[j] = 0;
	return (split);
}

/* int main (void)
{
	char *s = "hey|||>>ho  <echo> how< bci wtf		oo";
	char **split = mini_split(s);
	int i = 0;
	while (split[i])
	{
		printf("%s\n", split[i++]);
	}
} */