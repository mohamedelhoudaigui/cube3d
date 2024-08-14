/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 08:06:56 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 20:33:22 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

int	perform_dda(t_info *info, t_ray_info *ri, double *dist)
{
	int		hit;
	char	**map;

	hit = 0;
	map = info->map;
	while (!hit && ri->map_x >= 0 && ri->map_y >= 0)
	{
		calculate_step(ri, dist, info);
		if (ri->map_x >= 0 && ri->map_y >= 0)
		{
			if (map[ri->map_y][ri->map_x] != '0'
				&& map[ri->map_y][ri->map_x] != 'N'
				&& map[ri->map_y][ri->map_x] != 'S'
				&& map[ri->map_y][ri->map_x] != 'W'
				&& map[ri->map_y][ri->map_x] != 'E')
			{
				hit = 1;
			}
		}
	}
	return (hit);
}

void	draw_background(t_info *info)
{
	clear_window(info->mlx);
	put_floor_color(info, info->data->color_f);
	put_skye_color(info, info->data->color_c);
}

void	cast(t_info *info)
{
	t_vector	vector;
	double		dist;
	double		fov;
	int			x;
	double		ray_angle;

	if (info->player->vector.len == -1)
	{
		set_player_spawn(info);
		info->player->vector.len = -2;
	}
	draw_background(info);
	fov = info->player->fov;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = info->player->angle - fov / 2 + (x / (double)SCREEN_WIDTH)
			* fov;
		dist = raycast(info->player->vector.start, ray_angle, &vector, info);
		info->ray_angle = ray_angle;
		draw_wall_strip(info, x, dist, vector.end);
		x++;
	}
	check_reset_player_angle(info->player);
}
