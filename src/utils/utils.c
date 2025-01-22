/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:23:02 by xquah             #+#    #+#             */
/*   Updated: 2025/01/22 17:54:59 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_all(t_game *game)
{
	//ADD free the map
	free(game->map_data.wall_tex); // free the texture
}

int	validate_rgb(size_t color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FALSE);
	return (TRUE);
}

int	check_rgb_colors(t_map_data *map_data)
{
	if (!validate_rgb(map_data->f_rgb) || !validate_rgb(map_data->c_rgb))
		return (FALSE);
	return (TRUE);
}

int	open_file_and_allocate_map(char *file_path, t_game *game)
{
	game->temp_map = malloc(sizeof(char *) * (game->temp_rows + 1));
	if (!game->temp_map)
		return (-1);
	return (open(file_path, O_RDONLY));
}

int	process_line(char *line, t_game *game, int i)
{
	game->temp_map[i] = ft_strdup(line);
	if (!game->temp_map[i])
	{
		free_partial_temp(game, i);  // Free previously allocated memory
		return (-1);
	}
	return (0);
}
