/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:41:02 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 07:50:48 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_first_last_row(char **map, int height)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
			return (FAILURE);
		i++;
	}
	i = 0;
	while (map[height - 1][i])
	{
		if (map[height - 1][i] != '1' && map[height - 1][i] != ' '
			&& map[height - 1][i] != '\n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

// 1. if first = -1 & !\n, , first = len ( start)
// 2. if current character not space, update len=last
int check_row_edges(char **map, int row, int height)
{
    int len;
    int first;
    int last;

    len = 0;
    first = -1;
    last = -1;

    printf("Debug: Checking row edges for row %d\n", row);

    // Find the first and last non-space character in the row
    while (map[row][len] && map[row][len] != '\n')
    {
        if (map[row][len] != ' ' && first == -1)
            first = len;
        if (map[row][len] != ' ')
            last = len;
        len++;
    }

    printf("Debug: First non-space character at %d, last at %d\n", first, last);

    // If the row has no valid walls, skip
    if (first == -1 || last == -1)
    {
        printf("Debug: Row %d has no valid walls, skipping\n", row);
        return (SUCCESS);
    }

    // Check the edges of the row (ensure they are walls)
    if (map[row][first] != '1' || map[row][last] != '1')
    {
        printf("Debug: Row %d edges are not walls (first: %c, last: %c)\n", row, map[row][first], map[row][last]);
        return (FAILURE);
    }

    // Validate enclosed spaces inside the row
    len = first;
    while (len <= last)
    {
        if (map[row][len] == '0' || map[row][len] == 'N' || map[row][len] == 'S'
            || map[row][len] == 'E' || map[row][len] == 'W')
        {
            printf("Debug: Found character '%c' at position (%d, %d)\n", map[row][len], row, len);

            // Check above, below, left, and right of each '0' or valid character
            if (row > 0 && map[row - 1][len] == ' ')
            {
                printf("Debug: Character above (%d, %d) is a space\n", row - 1, len);
                return (FAILURE);
            }
            if (row < height - 1 && map[row + 1][len] == ' ')
            {
                printf("Debug: Character below (%d, %d) is a space\n", row + 1, len);
                return (FAILURE);
            }
            if (len > 0 && map[row][len - 1] == ' ')
            {
                printf("Debug: Character to the left (%d, %d) is a space\n", row, len - 1);
                return (FAILURE);
            }
            if (map[row][len + 1] == ' ')
            {
                printf("Debug: Character to the right (%d, %d) is a space\n", row, len + 1);
                return (FAILURE);
            }
        }
        len++;
    }

    printf("Debug: Row %d is properly enclosed by walls\n", row);
    return (SUCCESS);
}



int	check_config_identifier(char *line, int i)
{
	if ((line[i] == 'N' && line[i + 1] == 'O')
		|| (line[i] == 'S' && line[i + 1] == 'O')
		|| (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A')
		|| line[i] == 'F' || line[i] == 'C')
		return (1);
	return (0);
}

// 1. while - iterate each row up to height
// 2. while [i][j] - iteract each character in each row
// 3. if found player char
int	count_players(t_game *game, int map_start)
{
	int	i;
	int	j;
	int	player_count;

	i = map_start;
	player_count = 0;
	while (i < game->map_data.height)
	{
		j = 0;
		while (game->map_data.map[i][j])
		{
			if (is_player_char(game->map_data.map[i][j]))
			{
				player_count++;
				if (player_count == 1)
					set_player_position(game, i, j, map_start);
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

// divide half ( left, right)
void	set_player_position(t_game *game, int i, int j, int map_start)
{
	game->player.pos_x = (double)j + 0.5;
	game->player.pos_y = (double)(i - map_start) + 0.5;
	game->player.dir = game->map_data.map[i][j];
	player_north_south(game, i, j);
	player_east_west(game, i, j);
}