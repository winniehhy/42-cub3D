/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2025/01/21 12:35:20 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int draw_loop(t_game *game)
{
    move_player(game, &game->player);
    clear_image(game);
    set_ceiling_floor(game);
    raycast(game);
    draw_torch(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

void setup_hooks(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
    mlx_hook(game->win, 6, 1L << 6, mouse_pov, game);
    mlx_loop_hook(game->mlx, draw_loop, game);
}

int main(int ac, char **av)
{
    t_game game;
    
    init_all(&game, av[1], av[2]);
    if (go_to_check_file(av[1], &game) == FAILURE)
    {
        return (1);
    }
    printf("Debug: File checked successfully\n");
    map_checking(&game);
    
    // Print all debug information
    // print_map_data_debug(&game);
    
    setup_hooks(&game);
    printf("Debug: Setup hooks\n");

    mlx_loop(game.mlx);
    printf("Debug: MLX loop\n");
    return (0);
}


// /**
//  * Prints debug information about a texture
//  */
// void print_texture_debug(t_img *texture, const char *direction)
// {
//     if (!texture || !texture->img)
//         printf("Debug: %s texture is NULL\n", direction);
//     else
//         printf("Debug: %s texture - Width: %d, Height: %d, Address: %p\n",
//                direction,
//                texture->width,
//                texture->height,
//                texture->addr);
// }

// /**
//  * Extracts and prints RGB components from a size_t color value
//  */
// void print_rgb_debug(size_t color, const char *type)
// {
//     int r = (color >> 16) & 0xFF;
//     int g = (color >> 8) & 0xFF;
//     int b = color & 0xFF;
    
//     printf("Debug: %s RGB: R(%d), G(%d), B(%d)\n", type, r, g, b);
// }

// /**
//  * Prints all map data debug information
//  */
// void print_map_data_debug(t_game *game)
// {
//     printf("\n=== DEBUG MAP DATA ===\n");
    
//     // Print map dimensions
//     printf("\nMap Dimensions: %d x %d\n", game->map_data.width, game->map_data.height);
    
//     // Print map content
//     printf("\nMap Content:\n");
//     for (int y = 0; y < game->map_data.height; y++)
//     {
//         for (int x = 0; x < game->map_data.width; x++)
//         {
//             printf("%c", game->map_data.map[y][x]);
//         }
//         printf("\n");
//     }
    
//     // Print texture information
//     printf("\nTexture Information:\n");
//     print_texture_debug(&game->map_data.wall_tex[NORTH], "North");
//     print_texture_debug(&game->map_data.wall_tex[SOUTH], "South");
//     print_texture_debug(&game->map_data.wall_tex[EAST], "East");
//     print_texture_debug(&game->map_data.wall_tex[WEST], "West");
    
//     // Print RGB values
//     printf("\nColor Information:\n");
//     print_rgb_debug(game->map_data.c_rgb, "Ceiling");
//     print_rgb_debug(game->map_data.f_rgb, "Floor");
    
//     printf("\n=== END DEBUG DATA ===\n\n");
// }
