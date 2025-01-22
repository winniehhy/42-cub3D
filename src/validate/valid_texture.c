/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:01:05 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 17:04:29 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	parse_directions(t_game *game, char *file_path)
{
	int		fd;
	char	*line;
	char	*tmp;
	bool	found[4];

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
	}
	close(fd);
	return (found[NORTH] && found[SOUTH] && found[WEST] && found[EAST]);
}

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
