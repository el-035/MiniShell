/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:14:14 by efittant          #+#    #+#             */
/*   Updated: 2024/10/30 15:14:27 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_content(int fd, char *temp)
{
	char		*buffer;
	int			bytes;

	bytes = 1;
	buffer = (char *)ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (free(temp), temp = NULL, NULL);
	while (bytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(temp), temp = NULL, NULL);
		buffer[bytes] = '\0';
		if (bytes == 0)
			break ;
		temp = ft_strjoin_gnl(temp, buffer);
		if (!temp)
			return (free(buffer), NULL);
	}
	if (!temp || (temp && !*temp))
		return (free(buffer), free(temp), temp = NULL, NULL);
	return (free(buffer), temp);
}

char	*current_line(char *temp)
{
	int		i;
	char	*line;
	int		len;

	line = NULL;
	i = -1;
	len = 0;
	while (temp[len] && temp[len] != '\n')
		len++;
	if (temp[len] == '\n')
		len++;
	line = (char *) ft_calloc_gnl((len + 1), sizeof(char));
	if (!line)
		return (NULL);
	while (++i < len)
		line[i] = temp[i];
	return (line);
}

char	*saveline(char *str)
{
	char	*temp;
	size_t	len;
	char	*nl;

	len = 0;
	nl = ft_strchr_gnl(str, '\n');
	if (!nl)
		return (free(str), str = NULL, ft_strdup_gnl(""));
	nl++;
	while (nl[len])
		len++;
	temp = (char *) malloc((len + 1) * sizeof(char));
	if (!temp)
		return (free(str), str = NULL, NULL);
	temp[len] = '\0';
	while (len-- > 0)
		temp[len] = nl[len];
	free (str);
	str = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_content(fd, temp);
	if (!temp)
		return (NULL);
	line = current_line(temp);
	if (!line)
		return (free(temp), temp = NULL, NULL);
	temp = saveline(temp);
	if (!temp)
		return (free(line), NULL);
	return (line);
}

/* 

#include <stdio.h>
#include <fcntl.h>

int main()
{
    char    *line;
    int fd;
	int i;

    fd = open("divina_commedia.txt", O_RDONLY);
	i = 0;
    while (1)
    {
		line = get_next_line(fd);
		printf("%s", line);
		if (!line)
			return (close(fd), 0);
		free(line);
		i++;
    }
    close(fd);
    return 0;
} */
