/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:56:34 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 18:26:34 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
