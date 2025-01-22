/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:29:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 18:20:31 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	parse_color_values(char *line, size_t *packed_color)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	char	*trimmed_line;

	if (!line || !packed_color)
		return (FAILURE);
	trimmed_line = line;
	while (*trimmed_line && (*trimmed_line == 'F' || *trimmed_line == 'C'
			|| *trimmed_line == ' ' || *trimmed_line == '\t'))
		trimmed_line++;
	colors = ft_split(trimmed_line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		if (colors)
			free_array(colors);
		return (FAILURE);
	}
	trim_color_values(colors);
	if (validate_color_values(colors, &r, &g, &b) == FAILURE)
		return (free_array(colors), FAILURE);
	free_array(colors);
	*packed_color = create_rgb(r, g, b);
	return (SUCCESS);
}

int	process_map_line(char *line, t_game *game)
{
	if (!line || !game)
		return (FAILURE);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line)
		return (SUCCESS);
	if (line[0] == 'F')
	{
		if (parse_color_values(line, &game->map_data.f_rgb) == FAILURE)
			return (print_err_msg("Invalid floor color format"), FAILURE);
	}
	else if (line[0] == 'C')
	{
		if (parse_color_values(line, &game->map_data.c_rgb) == FAILURE)
			return (print_err_msg("Invalid ceiling color format"), FAILURE);
	}
	return (SUCCESS);
}

int	process_color_line(char *line, t_game *game,
	int *floor_found, int *ceiling_found)
{
	if (*line)
	{
		if (line[0] == 'F' || line[0] == 'C')
		{
			if (process_map_line(line, game) == FAILURE)
				return (FAILURE);
			if (line[0] == 'F')
				*floor_found = 1;
			else
				*ceiling_found = 1;
		}
	}
	return (SUCCESS);
}

int	parse_map_colors(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		floor_found;
	int		ceiling_found;

	floor_found = 0;
	ceiling_found = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_err_msg("Cannot open map file"), FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (handle_color_line(line, game, &floor_found, &ceiling_found)
			== FAILURE)
		{
			close(fd);
			return (FAILURE);
		}
		if (floor_found && ceiling_found)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_colors(game, floor_found, ceiling_found));
}
