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

int	check_surrounding_walls(char **map, int row, int col)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = map[row - 1][col];
	down = map[row + 1][col];
	left = map[row][col - 1];
	right = map[row][col + 1];
	return (up == '1' && down == '1' && left == '1' && right == '1');
}

int	is_surrounded_by_walls(char **map, int row, int col, int height)
{
	int	curr_len;
	int	prev_len;
	int	next_len;

	if (row == 0 || row == height - 1)
		return (0);
	curr_len = 0;
	while (map[row][curr_len] && map[row][curr_len] != '\n')
		curr_len++;
	prev_len = 0;
	while (map[row - 1][prev_len] && map[row - 1][prev_len] != '\n')
		prev_len++;
	next_len = 0;
	while (map[row + 1][next_len] && map[row + 1][next_len] != '\n')
		next_len++;
	if (col == 0 || col >= curr_len - 1)
		return (0);
	if (col >= prev_len || col >= next_len)
		return (0);
	return (check_surrounding_walls(map, row, col));
}

int	is_position_valid(char **map, int row, int col, int height)
{
	if (row == 0 || row == height - 1)
		return (0);
	if (!map[row][col + 1] || !map[row][col - 1])
		return (0);
	if (map[row][col] == ' ' || map[row - 1][col] == ' '
		|| map[row + 1][col] == ' ' || map[row][col - 1] == ' '
		|| map[row][col + 1] == ' ')
		return (0);
	return (1);
}

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
