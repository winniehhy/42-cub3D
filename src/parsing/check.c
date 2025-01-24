/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:14:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/24 14:16:34 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*trim_leading_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}

//make sure map is the last section in the file
//is_map_line, make sure map_first not happen
bool	validate_map_section(int fd)
{
	char	*line;
	bool	map_started;

	map_started = false;
	line = get_next_line(fd);
	while (line)
	{
		if (!check_map_section(line, &map_started))
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

bool	validate_map_position(const char *file_path)
{
	int		fd;
	bool	result;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_err_msg("Error opening file");
		return (false);
	}
	result = validate_map_section(fd);
	close(fd);
	return (result);
}

//strict ensure that the first & last row are all walls
int	check_row_validity(char **map, int row)
{
	int	first;
	int	last;
	int	len;

	len = 0;
	first = -1;
	last = -1;
	while (map[row][len] && map[row][len] != '\n')
	{
		if (map[row][len] != ' ' && first == -1)
			first = len;
		if (map[row][len] != ' ')
			last = len;
		len++;
	}
	if (first == -1 || last == -1)
		return (SUCCESS);
	if (map[row][first] != '1' || map[row][last] != '1')
		return (FAILURE);
	return (SUCCESS);
}

//check if there is a space around the player
// -1 = up, 1 = down, -1 = left, 1 = right
int	check_space_around(char **map, int row, int len, int height)
{
	if (row > 0 && map[row - 1][len] == ' ')
		return (FAILURE);
	if (row < height - 1 && map[row + 1][len] == ' ')
		return (FAILURE);
	if (len > 0 && map[row][len - 1] == ' ')
		return (FAILURE);
	if (map[row][len + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}
