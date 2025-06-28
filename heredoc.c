#include "minishell.h"

int	create_hd_filename(char *name, int size, int index)
{
	int		hd_id;
	char	*id_str;
	int		fd;

	hd_id = 0;
	while (hd_id < 1000)
	{
		id_str = ft_itoa(index + hd_id);
		if (!id_str)
			return (0);
		if (ft_strlen("/tmp/heredoc_") + ft_strlen(id_str) + 1 > size)
			return (free(id_str), -1);
		(ft_strlcpy(name, "/tmp/heredoc_", size),
			ft_strlcat(name, id_str, size), free(id_str));
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
			return (fd);
		hd_id++;
	}
	return (perror("Open: "), -1);
}

int	set_heredoc_fds(t_cmd *cmd, int index)
{
	char	tmp_name[64];
	int		fd;
	int		i;

	fd = create_hd_filename(tmp_name, sizeof(tmp_name), index);
	if (fd < 0)
		return (perror("Open heredoc file: "), 0);
	cmd->in = ft_strdup(tmp_name);
	i = -1;
	while (cmd->hd_content && cmd->hd_content[++i])
	{
		write(fd, cmd->hd_content[i], ft_strlen(cmd->hd_content[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	return ( return_exit_code(0), 1);
}
