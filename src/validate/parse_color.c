/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:29:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 15:31:42 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Frees a string array.
 * 
 * @param arr The string array to free
 */
static void free_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

/**
 * Creates a packed RGB value from individual components
 * 
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @return Packed RGB value
 */
size_t create_rgb(int r, int g, int b)
{
    return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

/**
 * Parses RGB color values from a string
 * 
 * @param line Input string containing RGB values
 * @param packed_color Pointer to store the packed RGB value
 * @return SUCCESS if parsing successful, FAILURE otherwise
 */
static int parse_color_values(char *line, size_t *packed_color)
{
    char **colors;
    int r, g, b;
    char *trimmed_line;

    if (!line || !packed_color)
        return (FAILURE);

    // Skip the identifier (F/C) and any whitespace
    trimmed_line = line;
    while (*trimmed_line && (*trimmed_line == 'F' || *trimmed_line == 'C' || 
           *trimmed_line == ' ' || *trimmed_line == '\t'))
        trimmed_line++;

    colors = ft_split(trimmed_line, ',');
    if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
    {
        if (colors)
            free_array(colors);
        return (FAILURE);
    }

    // Trim whitespace from each color value
    for (int i = 0; i < 3; i++)
    {
        char *start = colors[i];
        char *end = colors[i] + strlen(colors[i]) - 1;
        
        while (*start && (*start == ' ' || *start == '\t'))
            start++;
        while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
            end--;
        *(end + 1) = '\0';
        
        if (start != colors[i])
            memmove(colors[i], start, strlen(start) + 1);
    }

    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);

    free_array(colors);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (FAILURE);

    *packed_color = create_rgb(r, g, b);

    return (SUCCESS);
}

/**
 * Processes a map file line to check for and parse color information.
 * 
 * @param line The line to process
 * @param game Game structure containing map data
 * @return SUCCESS if line processed successfully, FAILURE if error
 */
int process_map_line(char *line, t_game *game)
{
    if (!line || !game)
        return (FAILURE);

    // Skip leading whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;

    // Skip empty lines
    if (!*line)
        return (SUCCESS);

    // Parse floor color
    if (line[0] == 'F')
    {
        if (parse_color_values(line, &game->map_data.f_rgb) == FAILURE)
            return (print_err_msg("Invalid floor color format"), FAILURE);
    }
    // Parse ceiling color
    else if (line[0] == 'C')
    {
        if (parse_color_values(line, &game->map_data.c_rgb) == FAILURE)
            return (print_err_msg("Invalid ceiling color format"), FAILURE);
    }

    return (SUCCESS);
}

/**
 * Reads and parses color information from a map file.
 * 
 * @param file_path Path to the map file
 * @param game Game structure to store the parsed data
 * @return SUCCESS if colors parsed successfully, FAILURE otherwise
 */
int parse_map_colors(char *file_path, t_game *game)
{
    int fd;
    char *line;
    int floor_found;
    int ceiling_found;

    floor_found = 0;
    ceiling_found = 0;
    
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (print_err_msg("Cannot open map file"), FAILURE);

    line = get_next_line(fd);
    while (line != NULL)
    {
        if (*line)  // Skip empty lines
        {
            // Check for color identifiers
            if (line[0] == 'F' || line[0] == 'C')
            {
                if (process_map_line(line, game) == FAILURE)
                {
                    free(line);
                    close(fd);
                    return (FAILURE);
                }
                if (line[0] == 'F')
                    floor_found = 1;
                else
                    ceiling_found = 1;
            }
        }
        free(line);
        
        // Break if both colors are found
        if (floor_found && ceiling_found)
            break;
            
        line = get_next_line(fd);
    }
    close(fd);

    // Verify that both colors were found and are valid
    if (!floor_found || !ceiling_found)
        return (print_err_msg("Missing floor or ceiling color"), FAILURE);

    check_rgb_colors(&game->map_data);
    return (SUCCESS);
}

