/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:14:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/24 12:26:28 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*trim_leading_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}

//make sure map is the last section in the file
//is_map_line, make sure map_first not happen
bool validate_map_section(int fd)
{
    char *line;
    bool map_started = false;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed_line = trim_leading_spaces(line);
        
        if (*trimmed_line == '\0')
        {
            free(line);
            continue;
        }
        
        if (is_map_line(trimmed_line))
            map_started = true;
        else if (map_started)
        {
            print_err_msg("Error: Map must be the last section in the file.\n");
            free(line);
            return (false);
        }
        
        free(line);
    }
    return (true);
}

bool validate_map_position(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        print_err_msg("Error opening file");
        return (false);
    }
    
    bool result = validate_map_section(fd);
    
    close(fd);
    return (result);
}

int	check_row_validity(char **map, int row)
{
	int	first;
	int	last;
	int	len;

	len = 0;
	first = -1;
	last = -1;
	while (map[row][len] && map[row][len] != '\n')
	{
		if (map[row][len] != ' ' && first == -1)
			first = len;
		if (map[row][len] != ' ')
			last = len;
		len++;
	}
	if (first == -1 || last == -1)
		return (SUCCESS);
	if (map[row][first] != '1' || map[row][last] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	check_space_around(char **map, int row, int len, int height)
{
	if (row > 0 && map[row - 1][len] == ' ')
		return (FAILURE);
	if (row < height - 1 && map[row + 1][len] == ' ')
		return (FAILURE);
	if (len > 0 && map[row][len - 1] == ' ')
		return (FAILURE);
	if (map[row][len + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}
