/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:26:58 by xquah             #+#    #+#             */
/*   Updated: 2025/01/23 14:08:08 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_up(t_game *game)
{
	game->player.pos_x += game->player.dir_x * MV_SPD;
	game->player.pos_y += game->player.dir_y * MV_SPD;
}

void	move_down(t_game *game)
{
	game->player.pos_x -= game->player.dir_x * MV_SPD;
	game->player.pos_y -= game->player.dir_y * MV_SPD;
}

void	move_left(t_game *game)
{
	game->player.pos_x += game->player.dir_y * MV_SPD;
	game->player.pos_y -= game->player.dir_x * MV_SPD;
}

void	move_right(t_game *game)
{
	game->player.pos_x -= game->player.dir_y * MV_SPD;
	game->player.pos_y += game->player.dir_x * MV_SPD;
}
