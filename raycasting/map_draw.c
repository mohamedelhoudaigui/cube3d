/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:24:05 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/05 02:15:44 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    line_dir(t_vector *map_elements, bool mode, int *value)
{
	if (mode == 0)
	{
		if (map_elements->x_start > map_elements->x_finish)
			(*value)--;
		else if (map_elements->x_start < map_elements->x_finish)
			(*value)++;
	}
	else if (mode == 1)
	{   
		if (map_elements->y_start > map_elements->y_finish)
			(*value)--;
		else if (map_elements->y_start < map_elements->y_finish)
			(*value)++;
	}
}

void    draw_map_line(t_vector *map_element, t_mlx *mlx_struct, t_data *img)
{
	int i;
	int j;

	i = map_element->y_start;
	while (i != map_element->y_finish)
	{
		j = map_element->x_start;
		while (j != map_element->x_finish)
		{
			my_mlx_pixel_put(img, j, i, get_char_color(map_element->map_char));
			line_dir(map_element, 0, &j);
		}
		line_dir(map_element, 1, &i);
	}
}

void    draw_square(t_vector *map_element, t_mlx *mlx_struct)
{
	int i;
	int j;

	i = map_element->y_start;
	while (i < map_element->y_finish)
	{
		draw_map_line(map_element, mlx_struct, mlx_struct->img);
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
	draw_rays(mlx_struct);
}
