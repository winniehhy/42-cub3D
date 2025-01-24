/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:50:39 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 23:54:44 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	convert_spaces_to_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_data.height)
	{
		j = 0;
		while (game->map_data.map[i][j])
		{
			if (game->map_data.map[i][j] == ' ')
				game->map_data.map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	check_map_chars_row(char **map, int row)
{
	int	j;

	j = 0;
	while (map[row][j])
	{
		if (!is_valid_map_char(map[row][j]) && map[row][j] != '\n'
			&& map[row][j] != ' ')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_extra_characters_after_last_row(char **map, int height)
{
	int	i;
	int	j;

	i = height - 1;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != '0')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
