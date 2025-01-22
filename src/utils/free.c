/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:55:56 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 17:04:57 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_map(char **map)
{
    int i = 0;

    if (map == NULL)
        return;

    while (map[i])
    {
        free(map[i]);
        map[i] = NULL;
        i++;
    }
    free(map);
}

void free_textures(t_img *wall_tex, void *mlx)
{
    int i = 0;

    while (i < 4)
    {
        if (wall_tex[i].img)
        {
            mlx_destroy_image(mlx, wall_tex[i].img);
            wall_tex[i].img = NULL;
        }
        i++;
    }
}

void free_mlx_resources(void *mlx, void *win)
{
    if (win)
    {
        mlx_destroy_window(mlx, win);
        win = NULL;
    }
    if (mlx)
    {
        mlx_destroy_display(mlx);
        free(mlx);
        mlx = NULL;
    }
}

void free_game_resources(t_game *game)
{
    if (game == NULL)
        return;

    free_map(game->map_data.map);
    free_textures(game->map_data.wall_tex, game->mlx);
    free_mlx_resources(game->mlx, game->win);
}

void	free_all(t_game *game)
{
	//ADD free the map
	free(game->map_data.wall_tex); // free the texture
}
