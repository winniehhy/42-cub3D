/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:01:05 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 20:05:28 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * validate_xpm_format - Validates if the given file path is a valid `.xpm` file.
 * @path: The file path to validate.
 * 
 * Checks if the file path is not NULL, has the `.xpm` extension, and
 * if the file exists and can be opened for reading.
 * 
 * Return: TRUE if valid, FALSE otherwise.
 */
int	validate_xpm_format(char *path)
{
	int	fd;

	if (!path)
		return (FALSE);
	if (!ft_strnstr(path, ".xpm", ft_strlen(path)))
		return (FALSE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

/**
 * process_direction - Processes and loads a texture for a specific direction.
 * @line: The line containing the texture path.
 * @game: Pointer to the game structure.
 * @direction: The direction (NORTH, SOUTH, WEST, EAST) being processed.
 * 
 * Extracts the texture path from the line, removes any trailing newline,
 * and attempts to load the texture for the specified direction.
 * 
 * Return: TRUE if successful, FALSE otherwise.
 */
int	process_direction(char *line, t_game *game, int direction)
{
	char	*path;
	char	*newline;

	line += 2;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	path = ft_strdup(line);
	if (!path)
		return (FALSE);
	newline = ft_strchr(path, '\n');
	if (newline)
		*newline = '\0';
	if (!load_texture(game, &(game->map_data.wall_tex[direction]), path))
	{
		free(path);
		return (FALSE);
	}
	free(path);
	return (TRUE);
}

/**
 * check_direction - Checks and processes a texture for a specific direction.
 * @tmp: The line containing the direction and texture path.
 * @game: Pointer to the game structure.
 * @found: Array tracking whether textures for directions are already found.
 * 
 * Parses the line to identify the direction (NO, SO, WE, EA) and
 * ensures it has not already been processed. If valid, processes the texture.
 * 
 * Return: Always returns 1 (used to continue parsing).
 */
int	check_direction(char *tmp, t_game *game, bool *found)
{
	if (ft_strncmp(tmp, "NO", 2) == 0 && !found[NORTH])
		found[NORTH] = process_direction(tmp, game, NORTH);
	else if (ft_strncmp(tmp, "SO", 2) == 0 && !found[SOUTH])
		found[SOUTH] = process_direction(tmp, game, SOUTH);
	else if (ft_strncmp(tmp, "WE", 2) == 0 && !found[WEST])
		found[WEST] = process_direction(tmp, game, WEST);
	else if (ft_strncmp(tmp, "EA", 2) == 0 && !found[EAST])
		found[EAST] = process_direction(tmp, game, EAST);
	return (1);
}

/**
 * parse_directions - Parses a map file to load textures for all directions.
 * @game: Pointer to the game structure.
 * @file_path: The path to the map file.
 * 
 * Reads the map file line by line and extracts texture paths for the
 * NORTH, SOUTH, WEST, and EAST directions. Ensures all directions are found.
 * 
 * Return: TRUE if all directions are successfully loaded, FALSE otherwise.
 */
int	parse_directions(t_game *game, char *file_path)
{
	int		fd;
	char	*line;
	char	*tmp;
	bool	found[4];

	if (!game || !file_path)
		return (FALSE);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	ft_memset(found, 0, sizeof(found));
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = line;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		check_direction(tmp, game, found);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (found[NORTH] && found[SOUTH] && found[WEST] && found[EAST]);
}

/**
 * validate_loaded_textures - Validates the loaded textures for correctness.
 * @game: Pointer to the game structure.
 * 
 * Checks that all textures are properly loaded, have valid dimensions,
 * and contain non-null image and address data.
 * 
 * Return: TRUE if all textures are valid, FALSE otherwise.
 */
int	validate_loaded_textures(t_game *game)
{
	int		i;
	t_img	*textures;

	if (!game->map_data.wall_tex)
		return (FALSE);
	textures = game->map_data.wall_tex;
	i = 0;
	while (i < 4)
	{
		if (!textures[i].img || !textures[i].addr)
			return (FALSE);
		if (textures[i].width <= 0 || textures[i].height <= 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
