/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:29:38 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 10:26:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// main - map_checking
int	map_checking(t_game *game)
{
	if (game->map_data.height < 3)
		return (print_err_msg("Map must have at least 3 rows"), FAILURE);
	if (!validate_map_walls(game))
		return (print_err_msg("Map must be enclosed by walls"), FAILURE);
	if (!validate_player_start(game))
		return (print_err_msg("Map must have exactly one player"), FAILURE);
	if (!validate_map_chars(game))
		return (print_err_msg("Map contains invalid characters"), FAILURE);
	convert_spaces_to_walls(game);
	return (SUCCESS);
}

// validate where all walls are properly closed
int	validate_map_walls(t_game *game)
{
	char	**map;
	int		map_start;
	int		height;
	int		i;

	map_start = find_map_start(game->map_data.map, game->map_data.height);
	if (map_start == -1)
		return (FAILURE);
	map = &(game->map_data.map[map_start]);
	height = game->map_data.height - map_start;
	if (check_first_last_row(map, height) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < height)
	{
		if (check_row_edges(map, i, height) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

// find map start and start count player
int	validate_player_start(t_game *game)
{
	int	map_start;
	int	player_count;

	map_start = find_map_start(game->map_data.map, game->map_data.height);
	if (map_start == -1)
		return (FAILURE);
	player_count = count_players(game, map_start);
	if (player_count == 1)
		return (SUCCESS);
	else
		return (FAILURE);
}

// check within the map have N, S, E, W, 0, 1
int	validate_map_chars(t_game *game)
{
	int	i;
	int	map_start;

	map_start = find_map_start(game->map_data.map, game->map_data.height);
	if (map_start == -1)
		return (FAILURE);
	i = map_start;
	while (i < game->map_data.height)
	{
		if (check_map_chars_row(game->map_data.map, i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
