/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:40:59 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 14:03:01 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	toggle_mouse(t_game *game)
{
	game->player.mouse = !game->player.mouse;
	if (game->player.mouse)
	{
		mlx_mouse_show(game->mlx, game->win);
		game->player.left_rotate = false;
		game->player.right_rotate = false;
	}
	else
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	}
}

int	mouse_pov(int x, int y, t_game *game)
{
	static int	old_x;
	int			diff_x;

	(void) y;
	if (!game->player.mouse)
	{
		diff_x = x - old_x;
		if (diff_x > 0)
			rotate_right(game);
		else if (diff_x < 0)
			rotate_left(game);
		if (old_x > SCREENWIDTH - 100)
			mlx_mouse_move(game->mlx, game->win,
				SCREENHEIGHT / 2, SCREENHEIGHT / 2);
		if (old_x < 100)
			mlx_mouse_move(game->mlx, game->win,
				SCREENWIDTH / 2, SCREENHEIGHT / 2);
	}
	old_x = x;
	return (0);
}
