/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:28 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 12:33:58 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int validate_unique_elements(t_file_elements *elements)
{
    // Check texture direction counts
    if (elements->no_count > 1 || elements->so_count > 1 || 
        elements->we_count > 1 || elements->ea_count > 1)
        return (FALSE);

    // Check color counts
    if (elements->floor_count > 1 || elements->ceiling_count > 1)
        return (FALSE);

    return (TRUE);
}

void free_file_elements(t_file_elements *elements)
{
    free(elements->no_path);
    free(elements->so_path);
    free(elements->we_path);
    free(elements->ea_path);
    ft_memset(elements, 0, sizeof(t_file_elements));
}