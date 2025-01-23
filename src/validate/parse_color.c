/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:29:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 16:07:51 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// << bitwise left shift operator
// R : 16 bit to left, first 24 byte
size_t	create_rgb(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

// 1. trim line till get the actual color value
// 2. validate trim color if is R, G, B
int	parse_color_values(char *line, size_t *packed_color)
{
	char	**colors;
	int		r;
	int		g;
	int		b;
	char	*trimmed_line;

	if (!line || !packed_color)
		return (FAILURE);
	trimmed_line = line;
	while (*trimmed_line && (*trimmed_line == 'F' || *trimmed_line == 'C'
			|| *trimmed_line == ' ' || *trimmed_line == '\t'))
		trimmed_line++;
	colors = ft_split(trimmed_line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		if (colors)
			free_array(colors);
		return (FAILURE);
	}
	trim_color_values(colors);
	if (validate_color_values(colors, &r, &g, &b) == FAILURE)
		return (free_array(colors), FAILURE);
	free_array(colors);
	*packed_color = create_rgb(r, g, b);
	return (SUCCESS);
}

//process line then store to struct
//parse color for F and C to f_rgb  & c_rgb
int process_map_line(char *line, t_game *game)
{
    if (!line || !game)
        return (FAILURE);

    // Trim leading whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;

    // Reject empty or invalid lines
    if (!*line)
        return (SUCCESS);

    // Process 'F' or 'C' lines
    if (line[0] == 'F')
    {
        if (parse_color_values(line, &game->map_data.f_rgb) == FAILURE)
            return (print_err_msg("Invalid floor color format"), FAILURE);
    }
    else if (line[0] == 'C')
    {
        if (parse_color_values(line, &game->map_data.c_rgb) == FAILURE)
            return (print_err_msg("Invalid ceiling color format"), FAILURE);
    }
    else
    {
        // Any line that isn't 'F' or 'C' is invalid
        return (print_err_msg("Invalid line format"), FAILURE);
    }

    return (SUCCESS);
}

//check whether F , C is found
int process_color_line(char *line, t_game *game, int *floor_found, int *ceiling_found)
{
    if (!line || strlen(line) == 0) // Skip empty or null lines
    {
        printf("Debug: Skipping empty or null line\n");
        return (SUCCESS);
    }

    // Trim leading whitespace
    while (*line == ' ' || *line == '\t')
        line++;

    printf("Debug: Processing line: %s\n", line);
    printf("Debug: Current flags - floor_found: %d, ceiling_found: %d\n", *floor_found, *ceiling_found);

    // Check if the line starts strictly with 'F' or 'C' followed by a space
    if ((line[0] == 'F' || line[0] == 'C') && (line[1] == ' ' || line[1] == '\t'))
    {
        // Check for duplicates BEFORE processing
        if (line[0] == 'F' && *floor_found)
        {
            printf("Debug: Duplicate floor color found! Line: %s\n", line);
            return (FAILURE);
        }
        if (line[0] == 'C' && *ceiling_found)
        {
            printf("Debug: Duplicate ceiling color found! Line: %s\n", line);
            return (FAILURE);
        }

        // Process the map line
        if (process_map_line(line, game) == FAILURE)
        {
            printf("Debug: Failed to process map line: %s\n", line);
            return (FAILURE);
        }

        // Update flags AFTER processing the line
        if (line[0] == 'F')
        {
            *floor_found = 1;
            printf("Debug: Setting floor_found to 1\n");
        }
        else if (line[0] == 'C')
        {
            *ceiling_found = 1;
            printf("Debug: Setting ceiling_found to 1\n");
        }
    }
    else
    {
        // If the line starts with 'Floor' or 'Ceiling' or any invalid keyword
        if (strncmp(line, "Floor", 5) == 0 || strncmp(line, "Ceiling", 7) == 0)
        {
            printf("Debug: Invalid color keyword detected: %s\n", line);
            return (FAILURE);
        }

        printf("Debug: Line does not specify 'F' or 'C', skipping: %s\n", line);
        return (SUCCESS); // Non-color lines are ignored as they may represent textures.
    }

    printf("Debug: Final flags - floor_found: %d, ceiling_found: %d\n", *floor_found, *ceiling_found);
    return (SUCCESS);
}






// parse map file and extract C and F color
// 1. call handle_color_line to read current line
// 2. if color found , then break
// 3. validate color found
int	parse_map_colors(char *file_path, t_game *game)
{
	int		fd;
	char	*line;
	int		floor_found;
	int		ceiling_found;

	floor_found = 0;
	ceiling_found = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_err_msg("Cannot open map file"), FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (handle_color_line(line, game, &floor_found, &ceiling_found)
			== FAILURE)
		{
			close(fd);
			return (FAILURE);
		}
		if (floor_found && ceiling_found)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_colors(game, floor_found, ceiling_found));
}
