/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:14:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/23 16:15:10 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool validate_map_position(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        perror("Error opening file");
        return false;
    }

    char line[1024];
    bool map_started = false;

    while (fgets(line, sizeof(line), file))
    {
        // Trim leading spaces
        char *trimmed_line = line;
        while (isspace(*trimmed_line))
            trimmed_line++;

        // Skip empty lines
        if (*trimmed_line == '\0')
            continue;

        // Check if map has started
        if (is_map_line(trimmed_line))
        {
            map_started = true;
        }
        else if (map_started) 
        {
            // If any non-map content appears after the map starts, it's invalid
            fclose(file);
            printf("Error: Map must be the last section in the file.\n");
            return false;
        }
    }

    fclose(file);
    return true;
}