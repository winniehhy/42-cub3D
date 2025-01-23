/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:05:37 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 17:21:43 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//trim all white space within color value
void	trim_color_values(char **colors)
{
	int		i;
	char	*start;
	char	*end;

	i = 0;
	while (i < 3)
	{
		start = colors[i];
		end = colors[i] + ft_strlen(colors[i]) - 1;
		while (*start && (*start == ' ' || *start == '\t'))
			start++;
		while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
			end--;
		*(end + 1) = '\0';
		if (start != colors[i])
			ft_memmove(colors[i], start, ft_strlen(start) + 1);
		i++;
	}
}

int	validate_color_values(char **colors, int *r, int *g, int *b)
{
	*r = ft_atoi(colors[0]);
	*g = ft_atoi(colors[1]);
	*b = ft_atoi(colors[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_color_line(char *line, t_game *game, int *floor_found,
		int *ceiling_found)
{
	if (process_color_line(line, game, floor_found, ceiling_found) == FAILURE)
	{
		free(line);
		return (FAILURE);
	}
	free(line);
	return (SUCCESS);
}

int	validate_colors(t_game *game, int floor_found, int ceiling_found)
{
	if (!floor_found || !ceiling_found)
	{
		print_err_msg("Missing floor or ceiling color");
		return (FAILURE);
	}
	check_rgb_colors(&game->map_data);
	return (SUCCESS);
}