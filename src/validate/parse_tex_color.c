/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:12:54 by hheng             #+#    #+#             */
/*   Updated: 2025/01/21 12:22:55 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Add this new function to parse RGB colors
int parse_rgb_color(char *line)
{
    char **parts;
    int rgb_values[3];
    size_t color;
    int i;

    // Skip identifier (F or C) and whitespace
    while (*line && (*line == 'F' || *line == 'C' || *line == ' ' || *line == '\t'))
        line++;

    parts = ft_split(line, ',');
    if (!parts)
        return (0);

    // Convert and validate each RGB component
    i = 0;
    while (i < 3 && parts[i])
    {
        char *trimmed = ft_strtrim(parts[i], " \t\n");
        if (!trimmed)
        {
            free_split(parts);
            return (0);
        }
        rgb_values[i] = ft_atoi(trimmed);
        free(trimmed);
        if (rgb_values[i] < 0 || rgb_values[i] > 255)
        {
            free_split(parts);
            return (0);
        }
        i++;
    }

    free_split(parts);
    
    if (i != 3)  // Make sure we got all three components
        return (0);

    // Combine RGB values into a single size_t
    color = (rgb_values[0] << 16) | (rgb_values[1] << 8) | rgb_values[2];
    return (color);
}

// Add this function to parse both floor and ceiling colors
int parse_colors(t_game *game, char *file_path)
{
    int fd;
    char *line;
    bool found_floor = false;
    bool found_ceiling = false;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (FALSE);

    while ((line = get_next_line(fd)) != NULL)
    {
        char *tmp = line;
        while (*tmp == ' ' || *tmp == '\t')
            tmp++;

        if (ft_strncmp(tmp, "F", 1) == 0 && !found_floor)
        {
            game->map_data.f_rgb = parse_rgb_color(tmp);
            found_floor = (game->map_data.f_rgb != 0);
        }
        else if (ft_strncmp(tmp, "C", 1) == 0 && !found_ceiling)
        {
            game->map_data.c_rgb = parse_rgb_color(tmp);
            found_ceiling = (game->map_data.c_rgb != 0);
        }

        free(line);
    }

    close(fd);
    return (found_floor && found_ceiling && check_rgb_colors(&game->map_data));
}

// Modify the main parsing function to handle both textures and colors
int parse_config(t_game *game, char *file_path)
{
    // First parse textures
    if (!parse_directions(game, file_path))
    {
        ft_putstr_fd("Error\nFailed to parse texture directions\n", 2);
        return (FALSE);
    }

    // Validate loaded textures
    if (!validate_loaded_textures(game))
    {
        ft_putstr_fd("Error\nFailed to validate textures\n", 2);
        return (FALSE);
    }

    // Then parse colors
    if (!parse_colors(game, file_path))
    {
        ft_putstr_fd("Error\nFailed to parse colors\n", 2);
        return (FALSE);
    }

    return (TRUE);
}

/**
 * Frees a NULL-terminated array of strings and the array itself
 * 
 * @param arr The array of strings to be freed
 */
void free_split(char **arr)
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