/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:01:05 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 14:04:52 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Validates if the given file path points to an .xpm file and is accessible.
 * 
 * @param path The file path to validate.
 * @return TRUE if the file is valid; otherwise FALSE.
 */
int validate_xpm_format(char *path)
{
    int fd;

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
 * Processes the texture for a specific direction by validating the path and loading the texture.
 * 
 * @param line The line containing the texture path.
 * @param game The game structure containing the map data.
 * @param direction The direction to process (NORTH, SOUTH, EAST, WEST).
 * @return TRUE if the texture was successfully processed; otherwise FALSE.
 */
int process_direction(char *line, t_game *game, int direction)
{
    char *path;

    line += 2;  // Skip the direction identifier (e.g., NO, SO)
    while (*line && (*line == ' ' || *line == '\t'))
        line++;

    path = ft_strdup(line);  // Make a copy of the path
    if (!path)
        return (FALSE);

    char *newline = ft_strchr(path, '\n');
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
 * Parses the texture directions (NO, SO, WE, EA) from a file.
 * 
 * @param game The game structure containing the map data.
 * @param file_path The path to the configuration file.
 * @return TRUE if all directions were successfully parsed; otherwise FALSE.
 */
int parse_directions(t_game *game, char *file_path)
{
    int fd;
    char *line;
    bool found[4] = {false, false, false, false};

    if (!game || !file_path)
        return (FALSE);

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (FALSE);

    while ((line = get_next_line(fd)) != NULL)
    {
        char *tmp = line;
        while (*tmp == ' ' || *tmp == '\t')
            tmp++;

        if (ft_strncmp(tmp, "NO", 2) == 0 && !found[NORTH])
            found[NORTH] = process_direction(tmp, game, NORTH);
        else if (ft_strncmp(tmp, "SO", 2) == 0 && !found[SOUTH])
            found[SOUTH] = process_direction(tmp, game, SOUTH);
        else if (ft_strncmp(tmp, "WE", 2) == 0 && !found[WEST])
            found[WEST] = process_direction(tmp, game, WEST);
        else if (ft_strncmp(tmp, "EA", 2) == 0 && !found[EAST])
            found[EAST] = process_direction(tmp, game, EAST);

        free(line);
    }

    close(fd);
    return (found[NORTH] && found[SOUTH] && found[WEST] && found[EAST]);
}

/**
 * Validates an RGB color value
 * 
 * @param color The RGB color value to validate
 * @return TRUE if valid, FALSE otherwise
 */
int validate_rgb(size_t color)
{
    int r;
    int g;
    int b;

    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (FALSE);
    return (TRUE);
}

/**
 * Checks the validity of floor and ceiling colors
 * 
 * @param map_data The map data containing RGB values
 * @return TRUE if valid, FALSE otherwise
 */
int check_rgb_colors(t_map_data *map_data)
{
    printf("Debug: Checking RGB colors\n");
    printf("Floor color: 0x%lx, Ceiling color: 0x%lx\n", 
           map_data->f_rgb, map_data->c_rgb);
    
    if (!validate_rgb(map_data->f_rgb) || !validate_rgb(map_data->c_rgb))
    {
        printf("Debug: Invalid RGB values detected\n");
        return (FALSE);
    }
    return (TRUE);
}

/**
 * Validates that all textures in the game are loaded correctly.
 * 
 * @param game The game structure containing texture data.
 * @return TRUE if all textures are valid; otherwise FALSE.
 */
int validate_loaded_textures(t_game *game)
{
    int i;
    t_img *textures;

    if (!game->map_data.wall_tex)
        return (FALSE);

    textures = game->map_data.wall_tex;
    for (i = 0; i < 4; i++)
    {
        if (!textures[i].img || !textures[i].addr)
            return (FALSE);
        if (textures[i].width <= 0 || textures[i].height <= 0)
            return (FALSE);
    }
    return (TRUE);
}
