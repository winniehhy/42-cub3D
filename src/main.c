/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2025/01/22 16:59:34 by hheng            ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_loop(t_game *game)
{
	move_player(game, &game->player);
	clear_image(game);
	set_ceiling_floor(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->win, 6, 1L << 6, mouse_pov, game);
	mlx_hook(game->win, 17, 0, close_window, game);;
	mlx_loop_hook(game->mlx, draw_loop, game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error: Invalid number of arguments!\n");
		return (false);
	}
	init_all(&game, av[1], av[2]);
	if (go_to_check_file(av[1], &game) == FAILURE)
	{
		return (1);
	}
	map_checking(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
