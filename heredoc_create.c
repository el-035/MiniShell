/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apchelni <apchelni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:54:42 by apchelni          #+#    #+#             */
/*   Updated: 2025/07/06 22:43:18 by apchelni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	realloc_heredoc(t_cmd *cmd, char *line, int *count)
{
	char	**new_lines;
	int		i;

	new_lines = ft_calloc(sizeof(char *), *count + 2);
	if (!new_lines)
		return (perror("Malloc: "), 0);
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

static void	print_hd_err(t_cmd *cmd)
{
	write(2, "warning: here-document delimited by end-of-file (wanted `", 57);
	write(2, cmd->limiter, ft_strlen(cmd->limiter));
	write(2, "')\n", 4);
}

static int	read_heredoc(t_cmd *cmd, int hd_flag, int count, char **envp)
{
	char	*line;

	while (return_sig_flag(-1) != 2)
	{
		line = readline("> ");
		if (!line)
			return (print_hd_err(cmd), 1);
		if (return_sig_flag(-1) == 2)
			break ;
		if (ft_strcmp(line, cmd->limiter) == 0)
			break ;
		if (ft_strchr(line, '$'))
		{
			if (hd_flag == 0)
				expand_var_hd(&line, envp);
			remove_useless_quotes(&line, return_final_len(line));
		}
		if (!realloc_heredoc(cmd, line, &count))
			return (free(line), 0);
	}
	if (line)
		free(line);
	return (1);
}

int	create_heredoc(t_cmd *cmd, char **envp)
{
	struct sigaction	sig;
	int					hd_flag;

	sig.sa_handler = &hd_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	hd_flag = 0;
	if ((ft_strchr(cmd->limiter, '\'') || ft_strchr(cmd->limiter, '"')))
	{
		remove_useless_quotes(&(cmd->limiter), return_final_len(cmd->limiter));
		hd_flag = 1;
	}
	if (!read_heredoc(cmd, hd_flag, 0, envp))
		return (0);
	return (1);
}
