/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:01:05 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 17:22:25 by hheng            ###   ########.fr       */
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

// 1. skip first two character
// 2. skip white sapce
// 3. dup (texture line) to path 
// 4. search for newline , then replace to null to remove 
// 5. call load_texture then free
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
	if (ft_strncmp(tmp, "NO", 2) == 0)
	{
		if (found[NORTH])
			return (FALSE); // Duplicate detected
		found[NORTH] = process_direction(tmp, game, NORTH);
	}
	else if (ft_strncmp(tmp, "SO", 2) == 0)
	{
		if (found[SOUTH])
			return (FALSE); // Duplicate detected
		found[SOUTH] = process_direction(tmp, game, SOUTH);
	}
	else if (ft_strncmp(tmp, "WE", 2) == 0)
	{
		if (found[WEST])
			return (FALSE); // Duplicate detected
		found[WEST] = process_direction(tmp, game, WEST);
	}
	else if (ft_strncmp(tmp, "EA", 2) == 0)
	{
		if (found[EAST])
			return (FALSE); // Duplicate detected
		found[EAST] = process_direction(tmp, game, EAST);
	}
	return (TRUE);
}

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
		if (!check_direction(tmp, game, found))
		{
			free(line);
			close(fd);
			return (FALSE); // Duplicate detected
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (found[NORTH] && found[SOUTH] && found[WEST] && found[EAST]);
}


// 1. check if is null == false
// 2. loop thru 4 wall
// 3. if null == false
// 4. if width/ height <= 0 = invalid
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