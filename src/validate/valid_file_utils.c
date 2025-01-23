/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:59:45 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 17:22:18 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//calculate number of line from input file
// open file , read and store to temp_row
int	get_temp_file_size(char *file_path, t_game *game)
{
	int		fd;
	char	*line;

	game->temp_rows = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		game->temp_rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

// create a temp_map from input file
int	create_temp_map(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_file_and_allocate_map(file_path, game);
	if (fd == -1)
		return (FAILURE);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL && i < game->temp_rows)
	{
		if (process_line(line, game, i) == -1)
		{
			free(line);
			close(fd);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->temp_map[i] = NULL;
	close(fd);
	return (SUCCESS);
}

//parse and validate temp_map
int	parse_temp_map(t_game *game)
{
	int	map_start;

	map_start = find_map_start(game->temp_map, game->temp_rows);
	if (map_start == -1)
		return (FAILURE);
	if (get_map_dimensions(game, map_start) == FAILURE)
		return (FAILURE);
	if (allocate_final_map(game) == FAILURE)
		return (FAILURE);
	if (copy_map_from_temp(game, map_start) == FAILURE)
	{
		free_map_data(game);
		return (FAILURE);
	}
	free_temp_map(game);
	return (SUCCESS);
}

//free entire temp_map
void	free_temp_map(t_game *game)
{
	int	i;

	if (!game || !game->temp_map)
		return ;
	i = 0;
	while (game->temp_map[i])
	{
		free(game->temp_map[i]);
		i++;
	}
	free(game->temp_map);
	game->temp_map = NULL;
}

//free up to the specific "current_row"
void	free_partial_temp(t_game *game, int current_row)
{
	int	i;

	i = 0;
	while (i < current_row)
	{
		free(game->temp_map[i]);
		i++;
	}
	free(game->temp_map);
}