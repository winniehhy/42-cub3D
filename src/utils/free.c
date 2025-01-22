/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:55:56 by hheng             #+#    #+#             */
/*   Updated: 2025/01/22 18:29:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_img *wall_tex, void *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (wall_tex[i].img)
		{
			mlx_destroy_image(mlx, wall_tex[i].img);
			wall_tex[i].img = NULL;
		}
		i++;
	}
}

void	free_mlx_resources(void *mlx, void *win)
{
	if (win)
	{
		mlx_destroy_window(mlx, win);
		win = NULL;
	}
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		mlx = NULL;
	}
}

void	free_game_resources(t_game *game)
{
	if (game == NULL)
		return ;
	free_map(game->map_data.map);
	free_textures(game->map_data.wall_tex, game->mlx);
	free_mlx_resources(game->mlx, game->win);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
