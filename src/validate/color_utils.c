/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:49:51 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 16:50:52 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_color_line(char *line, t_game *game, int *f_found, 
	int *c_found)
{
	if (*line)
	{
		if (line[0] == 'F' || line[0] == 'C')
		{
			if (process_map_line(line, game) == FAILURE)
				return (FAILURE);
			if (line[0] == 'F')
				*f_found = 1;
			else
				*c_found = 1;
		}
	}
	return (SUCCESS);
}

int	read_map_colors(int fd, t_game *game, int *f_found, int *c_found)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (handle_color_line(line, game, f_found, c_found) == FAILURE)
		{
			free(line);
			return (FAILURE);
		}
		free(line);
		if (*f_found && *c_found)
			break ;
		line = get_next_line(fd);
	}
	return (SUCCESS);
}