/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:33:48 by xquah             #+#    #+#             */
/*   Updated: 2025/01/22 19:18:22 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= SCREENWIDTH || y >= SCREENHEIGHT || x < 0 || y < 0)
		return ;
	dst = game->data + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void    clear_image(t_game *game)
{
	int x;
	int y;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		y = -1;
		while (++y < SCREENHEIGHT)
			my_mlx_pixel_put(game, x, y, 0);
	}
}

void    set_ceiling_floor(t_game *game)
{
    int x;
    int y;

    x = -1;
    while (++x < SCREENWIDTH)
    {
        y = -1;
        while (++y < SCREENHEIGHT)
        {
            if (y < SCREENHEIGHT / 2)
                my_mlx_pixel_put(game, x, y, game->map_data.c_rgb);
            else
                my_mlx_pixel_put(game, x, y, game->map_data.f_rgb);
        }
    }
}

/***
 * @brief The main raycasting function.
 * @brief Shoots a ray for every pixel of the screen width
 * @param game the game structure
 */
void	raycast(t_game *game)
{

     // Add these debug checks at the start
    if (!game->map_data.map) {
        printf("Error: map is NULL\n");
        return;
    }
    printf("Debug: Map dimensions: %d x %d\n", game->map_data.width, game->map_data.height);
    
    int x;
    
    x = -1;
    while (++x < SCREENWIDTH)
    {
        init_ray(&game->player, &game->ray, x);
        get_initial_dist(&game->player, &game->ray);
        dda_algo(game, &game->player, &game->ray);
        calc_wall_dist(&game->ray);
        draw_line_on_image(game, &game->ray, x);
    }
}
