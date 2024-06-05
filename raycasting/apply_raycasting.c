/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:11:16 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/05 04:24:18 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    draw_rays_img(t_mlx *mlx_struct)
{
	t_vector	*line;
	t_list		*rays;
	int			*value;
	int			x_offset;

	rays = mlx_struct->rays_inter;
	line = gb_malloc(sizeof(t_vector), 0);
	line->map_char = 'c';
	line->x_start = 0;
	line->x_finish = 1000;
	line->y_start = 0;
	line->y_finish = 500;
	draw_map_line(line, mlx_struct, mlx_struct->rays_img);
	line->map_char = 'f';
	line->y_start = 500;
	line->y_finish = 1000;
	draw_map_line(line, mlx_struct, mlx_struct->rays_img);
	x_offset = X / 90;
	line->x_start = 0;
	line->map_char = '.';
	while (rays)
	{
		value = rays->content;
		line->x_finish = line->x_start + x_offset;
		line->y_start = (Y - (*value / 2)) / 2;
		line->y_finish = ((Y - (*value / 2)) / 2) + *value;
		draw_map_line(line, mlx_struct, mlx_struct->rays_img);
		line->x_start += x_offset;
		rays = rays->next;
	}
}
