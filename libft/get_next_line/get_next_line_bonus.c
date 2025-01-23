/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:40:17 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 10:48:31 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*left_over[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	fill_buffer(fd, buffer, &left_over[fd]);
	free(buffer);
	if (!left_over[fd] || left_over[fd][0] == '\0')
		return (cleanup_and_return(&left_over[fd]));
	line = set_line(&left_over[fd]);
	if (!line)
		return (cleanup_and_return(&left_over[fd]));
	return (line);
}

static	char	*cleanup_and_return(char **left_over)
{
	if (*left_over)
	{
		free(*left_over);
		*left_over = NULL;
	}
	return (NULL);
}

char	*copy_line(char *left_over)
{
	char	*line;
	int		i;

	i = 0;
	if (line_len(left_over) == 0 && !ft_strchr_gnl(left_over, '\n'))
		return (NULL);
	line = malloc((line_len(left_over) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while ((left_over)[i] != '\n' && (left_over)[i])
	{
		line[i] = (left_over)[i];
		i++;
	}
	line[i] = (left_over)[i];
	if ((left_over)[i] != '\0')
		line[i + 1] = '\0';
	return (line);
}

char	*set_line(char **left_over)
{
	char	*line;
	char	*temp;

	if (!*left_over)
		return (NULL);
	temp = *left_over;
	line = copy_line(*left_over);
	*left_over = ft_strdup_gnl(*left_over + line_len(*left_over));
	if (!*left_over || !**left_over)
	{
		free(*left_over);
		*left_over = NULL;
	}
	free(temp);
	return (line);
}

void	fill_buffer(int fd, char *buffer, char **left_over)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return ;
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = *left_over;
		*left_over = ft_strjoin_special(temp, buffer, bytes_read);
		free(temp);
		temp = NULL;
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
}
