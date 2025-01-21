/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:59:45 by hheng             #+#    #+#             */
/*   Updated: 2025/01/21 12:25:31 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
* Counts the number of lines in the input file
* Updates game->temp_rows with the total line count
* Returns SUCCESS if file can be read, FAILURE otherwise
*/
int get_temp_file_size(char *file_path, t_game *game)
{
    int fd;
    char *line;
    
    game->temp_rows = 0;
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (FAILURE);
    while ((line = get_next_line(fd)))
    {
        game->temp_rows++;
        free(line);
    }
    close(fd);
    return (SUCCESS);
}

/*
* Creates temporary map storage by reading the input file
* Allocates memory and stores each line of the file
* Returns SUCCESS if creation succeeds, FAILURE if any step fails
*/
int create_temp_map(char *file_path, t_game *game)
{
    int fd;
    char *line;
    int i;

    game->temp_map = malloc(sizeof(char *) * (game->temp_rows + 1));
    if (!game->temp_map)
        return (FAILURE);
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (free(game->temp_map), FAILURE);
    i = 0;
    while ((line = get_next_line(fd)) && i < game->temp_rows)
    {
        game->temp_map[i] = ft_strdup(line);
        if (!game->temp_map[i])
        {
            free_partial_temp(game, i);
            free(line);
            close(fd);
            return (FAILURE);
        }
        free(line);
        i++;
    }
    game->temp_map[i] = NULL;
    close(fd);
    return (SUCCESS);
}

/*
* Processes temporary map into final map structure
* Handles dimension calculation, memory allocation, and data copying
* Returns SUCCESS if parsing succeeds, FAILURE if any step fails
*/
// int parse_temp_map(t_game *game)
// {
//     if (get_map_dimensions(game) == FAILURE)
//         return (FAILURE);
//     if (allocate_final_map(game) == FAILURE)
//         return (FAILURE);
//     if (copy_map_from_temp(game) == FAILURE)
//     {
//         free_map_data(game);
//         return (FAILURE);
//     }
//     free_temp_map(game);
//     return (SUCCESS);
// }

int parse_temp_map(t_game *game)
{
    int map_start;
    
    // Find where the actual map starts using existing function
    map_start = find_map_start(game->temp_map, game->temp_rows);
    if (map_start == -1)
        return (FAILURE);

    //  // First parse configuration (textures and colors)
    // if (parse_config(game, map_start) == FAILURE)
    //     return (FAILURE);

    // Calculate dimensions only for the actual map portion
    if (get_map_dimensions(game, map_start) == FAILURE)
        return (FAILURE);
    
    // Allocate memory for the final map
    if (allocate_final_map(game) == FAILURE)
        return (FAILURE);
    
    // Copy only the map portion
    if (copy_map_from_temp(game, map_start) == FAILURE)
    {
        free_map_data(game);
        return (FAILURE);
    }
    
    free_temp_map(game);
    return (SUCCESS);
}

/*
* Frees all memory allocated for temporary map
* Handles NULL checks and complete cleanup
*/
void free_temp_map(t_game *game)
{
    int i;

    if (!game || !game->temp_map)
        return;
    i = 0;
    while (game->temp_map[i])
    {
        free(game->temp_map[i]);
        i++;
    }
    free(game->temp_map);
    game->temp_map = NULL;
}

/*
* Frees partially allocated temporary map memory
* Used for cleanup when allocation fails mid-process
*/
void free_partial_temp(t_game *game, int current_row)
{
    int i;

    i = 0;
    while (i < current_row)
    {
        free(game->temp_map[i]);
        i++;
    }
    free(game->temp_map);
}
