/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 06:26:42 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 08:41:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    draw_line(t_vector *line, t_mlx *mlx_struct)
{
	double deltaX;
	double deltaY;
	int    pixels;

	deltaY = line->y_finish - line->y_start;
	deltaX = line->x_finish - line->x_start;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = line->x_start;
	double pixelY = line->y_start;
	while (pixels)
	{
		if (get_pixel(mlx_struct->img, pixelX, pixelY) == 92)
			break ;
		my_mlx_pixel_put(mlx_struct->img, pixelX, pixelY, get_char_color('.'));
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

void    draw_rays(t_mlx *mlx_struct)
{
	int         *player_pos;
	char        **map;
	int         offset;
	t_vector    *player_ray;
	int			length;
	int			finish_angle;
	int			start_angle;

	map = mlx_struct->map->map;
	player_pos = get_player_pos(map);
	if ((X / ft_strlen(map[0])) >= (Y / ft_doubleptr_size(map)))
		offset = Y / ft_doubleptr_size(map);
	else
		offset = X / ft_strlen(map[0]);
	length = 1000;
	player_pos[0] *= offset;
	player_pos[1] *= offset;
	player_ray = gb_malloc(sizeof(t_vector), 0);
	player_ray->x_start = player_pos[1] + (offset / 2);
	player_ray->y_start = player_pos[0] + (offset / 2);
	start_angle = mlx_struct->angle;
	finish_angle = mlx_struct->angle + 90;
	while (start_angle <= finish_angle)
	{
		double rad = start_angle * (PI / 180);
		player_ray->x_finish = player_ray->x_start + length * cos(rad);
		player_ray->y_finish = player_ray->y_start + length * sin(rad);
		player_ray->map_char = '.';
		draw_line(player_ray, mlx_struct);
		start_angle += 1;
	}
}
