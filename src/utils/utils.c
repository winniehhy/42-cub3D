/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:23:02 by xquah             #+#    #+#             */
/*   Updated: 2025/01/22 17:05:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_rgb(size_t color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FALSE);
	return (TRUE);
}

int	check_rgb_colors(t_map_data *map_data)
{
	if (!validate_rgb(map_data->f_rgb) || !validate_rgb(map_data->c_rgb))
		return (FALSE);
	return (TRUE);
}
