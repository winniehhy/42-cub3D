/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 14:27:28 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool valid_input(int ac, char *filepath)
{
       if (ft_strcmp(filepath + ft_strlen(filepath) - 4, ".cub") != 0)
    {
        printf("Error: Invalid file extension! Expected .cub file.\n");
        return false;
    }

    printf("Debug: Input is valid\n");
    return true;
}


int valid_file(char *file_path, t_game *game)
{
    if (get_temp_file_size(file_path, game) == FAILURE)
        return (FAILURE);
    if (create_temp_map(file_path, game) == FAILURE)
        return (FAILURE);
    if (parse_temp_map(game) == FAILURE)
    {
        free_temp_map(game);
        return (FAILURE);
    }
    printf("Debug: File is valid\n");
    return (SUCCESS);
    printf("Debug: Done valid file\n");
}

int valid_texture(t_game *game, char *file_path)
{
    if (!game || !game->mlx || !file_path)
        return (FALSE);
    if (!game->map_data.wall_tex)
        return (FALSE);
    if (!parse_directions(game, file_path))
        return (FALSE);
    printf("Debug: Done parse direction\n");
    if (!validate_loaded_textures(game))
        return (FALSE);
    printf("Debug: Done validate loaded textures\n");
    return (TRUE);
}

int go_to_check_file(char *file_path, t_game *game)
{
    if (!file_path || !game)
        return (print_err_msg("Invalid argument"), FAILURE);
        
    if (!valid_input(2, file_path))
        return (print_err_msg("Invalid input"), FAILURE);

    if (!valid_file(file_path, game))
        return (print_err_msg("Invalid file"), FAILURE);

    if (!valid_texture(game, file_path))
        return (print_err_msg("Invalid texture"), FAILURE);
    
    printf("Debug: Entering parse_map_color\n");
    if (parse_map_colors(file_path, game) == FAILURE)
        return (print_err_msg("Invalid map colors"), FAILURE);

    return (SUCCESS);
}
