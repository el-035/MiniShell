#include"minishell.h"

/* static int	ft_word_count(char *s, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			wc++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (wc);
} */

static char	*word(char *s, int i)
{
	char	*word;
	int		j;

	j = 0;
	while (is_space(s[i]) == 1 && s[i])
		i++;
	while (is_space(s[i]) == 0 && s[i])
	{
		i++;
		j++;
	}
	word = (char *) malloc((j + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = i - j;
	j = 0;
	while (is_space(s[i]) == 0 && s[i])
		word[j++] = s[i++];
	word[j] = '\0';
	return (word);
}

/* static char	**ft_free(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
		free(split[word]);
		word++;
	}
	free(split);
	return (NULL);
} */

char	**space_split(char const *s)
{
	int		wc;
	int		i;
	int		j;
	char	**split;

	wc = count_word((char *) s);
	i = 0;
	j = 0;
	
	split = (char **) ft_calloc ((wc + 1), sizeof(char *));
	if (!split)
		return (NULL);
	else
	{
		while (s && split && j < wc)
		{
			split[j++] = word((char *)s, i);
			if (!split[j - 1])
				return (free_split(split), NULL);
			while (is_space(s[i]) == 1)
				i++;
			i = i + ft_strlen(split[j - 1]) + 1;
		}
	}
	return (split);
}
