#include "minishell.h"

static int	ft_word_count(char *s)
{
	int	i;
	int	wc;
	int	f_quote;

	i = 0;
	wc = 0;
	f_quote = 0;
	while (s[i])
	{
		while ((s[i] == 32 || s[i] == 9))
			i++;
		if (!s[i])
			break ;
		wc++;
		while (s[i])
		{
			if (s[i] == 34 || s[i] == 39)
			{
				if (f_quote == 0)
					f_quote = s[i];
				else if (f_quote == s[i])
					f_quote = 0;
			}
			else if ((s[i] == 32 || s[i] == 9) && f_quote == 0)
				break ;
			i++;
		}
	}
	return (wc);
}

static int word_len(char *s, int i)
{
	int		j;
	int		f_quote;

	j = i;
	f_quote = 0;
	while ((s[i] == 32 || s[i] == 9))
		i++;
	if (!s[i])
		return 0;
	while(s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			if (f_quote == 0)
				f_quote = s[i];
			else if (f_quote == s[i])
				f_quote = 0;
		}
		else if ((s[i] == 32 || s[i] == 9) && f_quote == 0)
			break ;
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

char	**mini_split(char const *s)	//split pipes and <
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
