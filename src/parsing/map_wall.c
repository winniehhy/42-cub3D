/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:50:39 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 23:54:44 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map_chars_row(char **map, int row)
{
	int	j;

	j = 0;
	while (map[row][j])
	{
		if (!is_valid_map_char(map[row][j]) && map[row][j] != '\n'
			&& map[row][j] != ' ')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

bool	check_map_section(char *line, bool *map_started)
{
	char	*trimmed_line;

	trimmed_line = trim_leading_spaces(line);
	if (*trimmed_line == '\0')
		return (true);
	if (is_map_line(trimmed_line))
		*map_started = true;
	else if (*map_started)
	{
		print_err_msg("Map must be last section.\n");
		return (false);
	}
	return (true);
}
