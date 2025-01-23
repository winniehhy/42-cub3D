/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:40:00 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 23:53:24 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_err_msg(char *msg)
{
	printf("Error: %s\n", msg);
	printf("\n");
	exit(1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
