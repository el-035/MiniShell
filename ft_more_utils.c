#include "minishell.h"

char	*double_join(char *s1, char *s2, char *s3) // those are not allocated
{													//DO NOT PUT FAIL MALL HERE
	char	*tmp;
	char	*final;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, s3);
	if (!final)
		return (free(tmp), NULL);
	return (free(tmp), final);
}

void	check_if_dir(t_data *data, char *path, char *original)
{
	struct stat	sb;

	if (stat(path, &sb) == -1 || !ft_strcmp(original, ".."))
		return ;
	if (S_ISDIR(sb.st_mode))
	{
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		if (path != original)
			free(path);
		(free_split(data->envp), free_all(data), exit(126));
	}
}
