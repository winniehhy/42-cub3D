/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:48:45 by xquah             #+#    #+#             */
/*   Updated: 2025/01/23 14:05:42 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	touch(t_game *game, float px, float py)
{
	int	map_x;
	int	map_y;

	map_x = (int)px;
	map_y = (int)py;
	return (game->map_data.map[map_y][map_x] == '1'
		|| game->map_data.map[map_y][map_x] == ' ');
}

void	move_player(t_game *game, t_player *player)
{
	if (player->key_up && !touch(game, game->player.pos_x + game->player.dir_x
			* MV_SPD * 2, game->player.pos_y + game->player.dir_y * MV_SPD * 2))
		move_up(game);
	if (player->key_down && !touch(game, game->player.pos_x - game->player.dir_x
			* MV_SPD * 2, game->player.pos_y - game->player.dir_y * MV_SPD * 2))
		move_down(game);
	if (player->key_left && !touch(game, game->player.pos_x + game->player.dir_y
			* MV_SPD * 2, game->player.pos_y - game->player.dir_x * MV_SPD * 2))
		move_left(game);
	if (player->key_right
		&& !touch(game, game->player.pos_x - game->player.dir_y
			* MV_SPD * 2, game->player.pos_y + game->player.dir_x * MV_SPD * 2))
		move_right(game);
	if (player->left_rotate)
		rotate_left(game);
	if (player->right_rotate)
		rotate_right(game);
}
