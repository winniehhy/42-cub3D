/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:59:45 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 20:14:16 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * get_temp_file_size - Calculates the number of lines in the input file.
 * @file_path: Path to the file being processed.
 * @game: Pointer to the game structure, where the line count is stored.
 * 
 * Opens the file, reads each line, and increments the `temp_rows` field in the game structure.
 * Frees each line after reading to avoid memory leaks. Closes the file at the end.
 * 
 * Return: SUCCESS if the file is processed successfully, FAILURE if the file cannot be opened.
 */
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

/**
 * create_temp_map - Creates a temporary map representation from the input file.
 * @file_path: Path to the file being processed.
 * @game: Pointer to the game structure, where the temporary map is stored.
 * 
 * Opens the file and allocates memory for the temporary map.
 * Processes each line and stores it in the `temp_map` field of the game structure.
 * If any line fails to process, frees resources and returns FAILURE.
 * 
 * Return: SUCCESS if the map is created successfully, FAILURE otherwise.
 */
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

/**
 * parse_temp_map - Processes and validates the temporary map.
 * @game: Pointer to the game structure containing the temporary map.
 * 
 * Determines where the map starts, calculates dimensions, allocates memory for the final map,
 * and copies the validated map data from the temporary map. Frees the temporary map upon success.
 * If any step fails, frees resources and returns FAILURE.
 * 
 * Return: SUCCESS if the map is parsed and validated, FAILURE otherwise.
 */
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

/**
 * free_temp_map - Frees all memory allocated for the temporary map.
 * @game: Pointer to the game structure containing the temporary map.
 * 
 * Iterates through each row of the `temp_map` field, frees each row,
 * and then frees the entire temporary map. Sets the `temp_map` pointer to NULL.
 * 
 * Return: None.
 */
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

/**
 * free_partial_temp - Frees a partially created temporary map.
 * @game: Pointer to the game structure containing the temporary map.
 * @current_row: The number of rows successfully processed before an error occurred.
 * 
 * Frees all rows up to the specified `current_row` and then frees the map itself.
 * Used to clean up memory in case of an error during map creation.
 * 
 * Return: None.
 */
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
