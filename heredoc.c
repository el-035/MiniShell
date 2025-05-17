#include "minishell.h"

/*ft_strcmp(line, lim)
{

}*/

#include <string.h>

int exec_heredoc(t_input *here_doc, t_data *data)
{
	char	*lim;
	char *line;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	lim = here_doc->next->content;
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, lim) == 0)
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return 1;
}

int handle_heredoc(t_input *input, t_data *data)
{
	t_input *cur;
	t_input *start;

	cur = input;
	start = input;
	while (1)
	{
		if (cur->type == HERE_DOC)
			exec_heredoc(cur, data);
		cur = cur->next;
		if (cur == start)
			break ;
	}
	return (0);
}
