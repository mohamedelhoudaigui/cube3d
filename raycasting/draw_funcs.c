/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:24:05 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 02:07:10 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int get_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

int get_char_color(char map_char)
{
    int color;

    switch (map_char)
    {
        case '1' : 
            color = get_color(205, 92, 92);
            break ;
        case '0' :
            color = get_color(255, 255, 255);
            break ;
        case ' ' :
            color = get_color(0, 0, 0);
            break ;
        default :
            color = get_color(240, 230, 140);
            break ;
    }
    return (color);
}


void    draw_square(t_vector *map_element, t_mlx *mlx_struct)
{
    int i;
    int j;

    i = map_element->y_start;
    while (i < map_element->y_finish)
    {
        j = map_element->x_start;
        while (j < map_element->x_finish)
        {
            my_mlx_pixel_put(mlx_struct->img, j, i, get_char_color(map_element->map_char));
            j++;
        }
        i++;
    }
}

void    draw_map(t_mlx *mlx_struct)
{
    char    **map;
    int     i;
    int     j;
    int     x;
    int     y;
    int     offset;
    t_vector *map_element;

    
    i = 0;
    y = 0;
    map = mlx_struct->map->map;
    map_element = gb_malloc(sizeof(t_vector), 0);
    if ((X / ft_strlen(map[0])) >= (Y / ft_doubleptr_size(map)))
        offset = Y / ft_doubleptr_size(map);
    else
        offset = X / ft_strlen(map[0]);
    
    while (i < ft_doubleptr_size(map))
    {
        x = 0;
        j = 0;
        while (j < ft_strlen(map[0]))
        {
            map_element->map_char = map[i][j];
            map_element->x_start = x;
            map_element->x_finish = x + offset;
            map_element->y_start = y;
            map_element->y_finish = y + offset;
            draw_square(map_element, mlx_struct);
            x += offset;
            j++;
        }
        y += offset;
        i++;
    }
    mlx_put_image_to_window(mlx_struct->mlx_srv, mlx_struct->mlx_win, mlx_struct->img->img, 0, 0);
}
