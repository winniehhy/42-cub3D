/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:44:43 by xquah             #+#    #+#             */
/*   Updated: 2025/01/22 19:17:28 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Initialize the ray struct with the camera plane and direction
 */
void    init_ray(t_player *player, t_ray *ray, int x)
{
    ray->camera_perc = 2 * x / (double)SCREENWIDTH - 1;
    ray->dir_x = player->dir_x + player->plane_x * ray->camera_perc;
    ray->dir_y = player->dir_y + player->plane_y * ray->camera_perc;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    ray->delta_dist_x = fabs(1 / ray->dir_x); 
    ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/***
 * @brief Calculate the initial distance () of the ray to the wall
 */
void    get_initial_dist(t_player *player, t_ray *ray)
{
    if (ray->dir_x >= 0)
    {
        ray->map_step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x; //add start x
    }
    else
    {
        ray->map_step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x; //add start x
    }
    if (ray->dir_y >= 0)
    {
        ray->map_step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y; //add start y
    }
    else
    {
        ray->map_step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y; //add start y
    }
}

/***
 * @brief Perform the DDA algorithm to until it hits a wall
 * @param game the game structure
 * @param player the player structure
 * @param ray the ray structure
 */
void    dda_algo(t_game *game, t_player *player, t_ray *ray)
{
    int hit;

    hit = 0;
    // perform DDA
    while (hit == 0)
    {
        // jump to next map square, either in x-direction, or in y-direction
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->map_step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->map_step_y;
            ray->side = 1;
        }

          // Check map boundaries first
        if (ray->map_x < 0 || ray->map_x >= game->map_data.width ||
            ray->map_y < 0 || ray->map_y >= game->map_data.height)
        {
            hit = 1;  // Hit boundary
            break;
        }
        
        // Check if ray has hit a wall
        if (game->map_data.map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}
/***
 * @brief Calculate the distance to the wall fromt he camera plne (perpendicular distance)
 * @brief This is to fix the fish eye effect
 */
void    calc_wall_dist(t_ray *ray)
{
    if (ray->side == VERTICAL)
        ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else if (ray->side == HORIZONTAL)
        ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

/***
 * @brief Draw a single verical lines of the wall on the window image
 * @param game the game structure
 * @param ray the ray structure
 * @param x the x coordinate of the screen
 */
void    draw_line_on_image(t_game *game, t_ray *ray, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    
    line_height = (int)(SCREENHEIGHT / ray->wall_dist);
    draw_start = SCREENHEIGHT / 2 - line_height / 2;
    draw_end = SCREENHEIGHT / 2 + line_height / 2;
    while (draw_start < draw_end)
    {
        put_wall_texture(game, x, draw_start, line_height);
        draw_start++;
    }
}