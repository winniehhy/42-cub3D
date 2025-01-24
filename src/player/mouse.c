/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:40:59 by hheng             #+#    #+#             */
/*   Updated: 2025/01/24 14:41:49 by hheng            ###   ########.fr       */
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

//only track x-axis
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
