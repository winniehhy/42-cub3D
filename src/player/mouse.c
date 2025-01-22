/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:40:59 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 19:15:39 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int mouse_pov(int x, int y, t_game *game)
{
    static int old_x;
    int diff_x;

    (void)y;  // We don't use y coordinate for rotation
    
    // Only handle mouse motion if mouse is hidden (game mode)
    if (!game->player.mouse)
    {
        diff_x = x - old_x;
        if (diff_x > 0)
            rotate_right(game);
        else if (diff_x < 0)
            rotate_left(game);
            
        // Reset mouse position if it gets too close to screen edges
        if (old_x > SCREENWIDTH - 100)  // 100 pixels from edge
            mlx_mouse_move(game->mlx, game->win, SCREENHEIGHT / 2, SCREENHEIGHT / 2);
        if (old_x < 100)  // 100 pixels from edge
            mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
    }
    
    old_x = x;
    return (0);
}