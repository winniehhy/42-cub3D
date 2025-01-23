/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 11:49:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Initialize the player, map, texture
 * @param game the game structure
 * @param map_file the map file
 * @param texture_file the texture file (NOT currently in use)
*/
void	init_all(t_game *game, char *map_file, char *texture_file)
{
	ft_memset(game, 0, sizeof(t_game));
	init_player(&game->player);
	init_mlx(game);
	if (!init_texture(game))
	{
		printf("Error: Texture initialization failed\n");
		exit(EXIT_FAILURE);
	}
	game->map_data.map = NULL;
	game->map_data.width = 0;
	game->map_data.height = 0;
	mlx_mouse_hide(game->mlx, game->win);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}
