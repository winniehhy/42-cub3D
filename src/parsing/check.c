/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:14:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 19:17:57 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*trim_leading_spaces(char *line)
{
	while (isspace(*line))
		line++;
	return (line);
}

bool	validate_map_section(FILE *file)
{
	char	line[1024];
	bool	map_started;
	char	*trimmed_line;

	map_started = false;
	while (fgets(line, sizeof(line), file))
	{
		trimmed_line = trim_leading_spaces(line);
		if (*trimmed_line == '\0')
			continue ;
		if (is_map_line(trimmed_line))
			map_started = true;
		else if (map_started)
		{
			print_err_msg("Error: Map must be the last section in the file.\n");
			return (false);
		}
	}
	return (true);
}

bool	validate_map_position(const char *file_path)
{
	FILE	*file;
	bool	result;

	file = fopen(file_path, "r");
	if (!file)
	{
		print_err_msg("Error opening file");
		return (false);
	}
	result = validate_map_section(file);
	fclose(file);
	return (result);
}

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
