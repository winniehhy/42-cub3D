/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 11:22:13 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * valid_input - Validates the input file's extension.
 * @ac: The argument count (expected to be 2 for file validation).
 * @filepath: The path of the file provided as input.
 * 
 * Checks if the provided file has the `.cub` extension. If not, 
 * prints an error message and returns false.
 * 
 * Return: true if the file extension is valid, false otherwise.
 */
bool	valid_input(int ac, char *filepath)
{
	if (ft_strcmp(filepath + ft_strlen(filepath) - 4, ".cub") != 0)
	{
		printf("Error: Invalid file extension! Expected .cub file.\n");
		return (false);
	}
	return (true);
}

/**
 * valid_file - Validates the file and processes its contents for the game.
 * @file_path: The path to the file being validated.
 * @game: Pointer to the game structure.
 * 
 * Performs multiple validation and processing steps, including:
 * - Checking the temporary file size.
 * - Creating a temporary map from the file.
 * - Parsing the temporary map for further use.
 * If any of these steps fail, the function cleans up resources and
 * returns FAILURE.
 * 
 * Return: SUCCESS if all steps succeed, FAILURE otherwise.
 */
int	valid_file(char *file_path, t_game *game)
{
	if (get_temp_file_size(file_path, game) == FAILURE)
		return (FAILURE);
	if (create_temp_map(file_path, game) == FAILURE)
		return (FAILURE);
	if (parse_temp_map(game) == FAILURE)
	{
		free_temp_map(game);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * valid_texture - Validates and loads the textures for the game.
 * @game: Pointer to the game structure.
 * @file_path: The path to the map file containing texture information.
 * 
 * Checks if the game structure, its components, and the file path
 * are valid. Then it parses the directions and validates that all
 * textures are properly loaded and usable.
 * 
 * Return: TRUE if all textures are valid, FALSE otherwise.
 */
int	valid_texture(t_game *game, char *file_path)
{
	if (!game || !game->mlx || !file_path)
		return (FALSE);
	if (!game->map_data.wall_tex)
		return (FALSE);
	if (!parse_directions(game, file_path))
		return (FALSE);
	if (!validate_loaded_textures(game))
		return (FALSE);
	return (TRUE);
}

int	go_to_check_file(char *file_path, t_game *game)
{
	if (!file_path || !game)
		return (print_err_msg("Invalid argument"), FAILURE);
	if (!valid_input(2, file_path))
		return (print_err_msg("Invalid input"), FAILURE);
	if (!valid_file(file_path, game))
		return (print_err_msg("Invalid file"), FAILURE);
	if (!valid_texture(game, file_path))
		return (print_err_msg("Invalid texture"), FAILURE);
	if (parse_map_colors(file_path, game) == FAILURE)
		return (print_err_msg("Invalid map colors"), FAILURE);
	return (SUCCESS);
}
