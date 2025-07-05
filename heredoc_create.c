#include "minishell.h"

int	create_heredoc(t_cmd *cmd, char **envp)
{
	char *line;
	int count;
	char **new_lines;
	int	i;
	struct sigaction	sig;
	int hd_flag = 0;

	sig.sa_handler = &hd_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	//signal(SIGQUIT, SIG_IGN);
	count = 0;
	if ((ft_strchr(cmd->limiter, '\'') || ft_strchr(cmd->limiter, '"')))
		{
			remove_useless_quotes(&(cmd->limiter), return_final_len(cmd->limiter));
			hd_flag = 1;
		}
	while (return_sig_flag(-1) != 2)
	{
		line = readline("> ");
		if (!line)
		{
			write (2, "bash: warning: here-document delimited by end-of-file (wanted `", 64);
			write (2, cmd->limiter, ft_strlen(cmd->limiter));
			write (2, "')\n", 4);
			break ;
 		}
		if (return_sig_flag(-1) == 2)
		{
			//return_sig_flag(0);
			break ;
		}
		if (ft_strcmp(line, cmd->limiter) == 0)
			break ;
		if (ft_strchr(line, '$'))	
		{
			if (hd_flag == 0)
				expand_var(&line, envp);
			remove_useless_quotes(&line, return_final_len(line));
		}
		new_lines = ft_calloc(sizeof(char *), count + 2);
		if (!new_lines)
			return (perror("Malloc: "), 0);
		i = -1;
		while (++i < count)
			new_lines[i] = cmd->hd_content[i];
		new_lines[count] = line;
		new_lines[count + 1] = NULL;
		free(cmd->hd_content);
		cmd->hd_content = new_lines;
		count++;		
	}
	free(line);
	return (1);
}

/* int	create_heredoc(t_cmd *cmd, char **envp)
{
	int count;
	int	i;
	struct sigaction	sig;
	int hd_flag;

	sig.sa_handler = &hd_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	//signal(SIGQUIT, SIG_IGN);
	count = 0;
	hd_flag = 0;
	if ((ft_strchr(cmd->limiter, '\'') || ft_strchr(cmd->limiter, '"')))
	{
		remove_useless_quotes(&(cmd->limiter), return_final_len(cmd->limiter));
		hd_flag = 1;
	}
	while (1)
	{
		
		i = read_heredoc(cmd, hd_flag, &count, envp);
		if (i == 0)
			return (fail_mall(), 0);
		else if (i == 2)
			break ;				
	}
	return (1);
} */
/*

static int	realloc_heredoc(t_cmd *cmd, char *line, int *count)
{
	char **new_lines;
	int	i;

	new_lines = ft_calloc(sizeof(char *), (*count) + 2);
	if (!new_lines)
		return (0);
	i = -1;
	while (++i < *count)
		new_lines[i] = cmd->hd_content[i];
	new_lines[*count] = line;
	new_lines[*count + 1] = NULL;
	free(cmd->hd_content);
	cmd->hd_content = new_lines;
	(*count)++;
	return (1);
}

static int read_heredoc(t_cmd *cmd, int hd_flag, int *count, char **envp)
{
	char *line;

	line = readline("> ");
		if (!line)
		{
			write (2, "bash: warning: here-document delimited by end-of-file (wanted `", 64);
			write (2, cmd->limiter, ft_strlen(cmd->limiter));
			write (2, "')\n", 4);
			return (2);
 		}
		if (return_sig_flag(-1) == 2)
			//return_sig_flag(0);
			//free(line);
			return (2);
		if (ft_strcmp(line, cmd->limiter) == 0)
			//free(line);
			return (2);
		if (ft_strchr(line, '$'))	
		{
			if (hd_flag == 0)
				expand_var(&line, envp);
			remove_useless_quotes(&line, return_final_len(line));
		}
	if (!realloc_heredoc(cmd, line, count))
		//free(line);
		return (0);
	free(line);
	return (1);
}

*/
