/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:20:03 by xquah             #+#    #+#             */
/*   Updated: 2025/01/23 13:39:50 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Get the pixel color from an image given the x and y coordinates
 * @param tex the texture image
 * @param x the x coordinate on the image
 * @param y the y coordinate on the image
 */
unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

/***
 * @brief Get the side of the wall that the ray hit
 * @return the side of the wall (NORTH, SOUTH, EAST, WEST)
 */
int	get_wall_side(t_ray *ray)
{
	if (ray->side == VERTICAL)
	{
		if (ray->dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

/***
 * @brief Get the color of each pixel of the current vertical strip the wall 
 * @param game the game structure
 * @param scr_x the x coordinate of the screen
 * @param scr_y the y coordinate of the screen
 * @param line_height the height of the vertical strip of the wall
 */
void	put_wall_texture(t_game *game, int scr_x, int scr_y, int line_height)
{
	t_ray	*ray;
	int		side;
	int		tex_x;
	int		tex_y;
	double	tex_step_y;

	ray = &game->ray;
	side = get_wall_side(ray);
	if (ray->side == HORIZONTAL)
		ray->wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	else
		ray->wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	ray->wall_x -= floor((ray->wall_x));
	tex_x = (int)(ray->wall_x * (double) game->map_data.wall_tex[side].width);
	tex_step_y = (double) game->map_data.wall_tex[side].height
		/ (double) line_height;
	tex_y = (int)((double)(scr_y - (SCREENHEIGHT / 2 - line_height / 2))
			*tex_step_y);
	my_mlx_pixel_put(game, scr_x, scr_y,
		get_pixel_color(&game->map_data.wall_tex[side], tex_x, tex_y));
}
