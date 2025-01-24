/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:56:34 by hheng             #+#    #+#             */
/*   Updated: 2025/01/24 12:57:42 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// N : X = 0, Y = -1 ( facing upward) - getting smaller
// S : X = 0, Y = 1 ( facing downward) - getting bigger
void	player_north_south(t_game *game, int i, int j)
{
	if (game->map_data.map[i][j] == 'N')
	{
		game->player.dir = 'N';
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map_data.map[i][j] == 'S')
	{
		game->player.dir = 'S';
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

// W : X = -1, Y = 0 ( facing left)
// S : X = 1, Y = 0 ( facing right)
void	player_east_west(t_game *game, int i, int j)
{
	if (game->player.dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (game->player.dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

void	free_map_data(t_game *game)
{
	int	i;

	if (!game || !game->map_data.map)
		return ;
	i = 0;
	while (i < game->map_data.height)
	{
		free(game->map_data.map[i]);
		i++;
	}
	free(game->map_data.map);
	game->map_data.map = NULL;
}

// 1. check null
// 2. skip leading space
// 3. check config identifies ( No, SO, WE, EA,F, C)
// 4. check character is not a space, & is player ( 1,0)
int	is_map_line(char *line)
{
	int	i;
	int	has_valid_char;

	i = 0;
	has_valid_char = 0;
	if (!line || !*line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	if (check_config_identifier(line, i))
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& !is_player_char(line[i]) && line[i] != '\n')
			return (0);
		if (line[i] == '1' || line[i] == '0' || is_player_char(line[i]))
			has_valid_char = 1;
		i++;
	}
	return (has_valid_char);
}

/**
 * Finds the starting index of the map in a given array of strings.
 *
 * @map: A double pointer to the array of strings (lines of the map).
 * @height: The total number of lines in the array (map height).
 *
 * This function iterates through the array of strings to locate the first
 * line that satisfies the following conditions:
 * 1. The line is not NULL.
 * 2. The line has a non-zero length (not empty).
 * 3. The line is recognized as a valid map line (determined by is_map_line()).
 *
 * If a valid map line is found, the function returns its index.
 * If no valid map line is found, the function returns -1.
 * */
int	find_map_start(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i] && ft_strlen(map[i]) > 0 && is_map_line(map[i]))
			return (i);
		i++;
	}
	return (-1);
}
