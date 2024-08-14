/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:15:12 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 20:24:03 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

void	calculate_ray_length(t_ray_info *ri, t_point pos)
{
	if (ri->dir.x < 0)
	{
		ri->step.x = -1;
		ri->ray_len.x = (pos.x - ri->map_x * TILE_SIZE) * ri->ray_step.x
			/ TILE_SIZE;
	}
	else
	{
		ri->step.x = 1;
		ri->ray_len.x = ((ri->map_x + 1) * TILE_SIZE - pos.x) * ri->ray_step.x
			/ TILE_SIZE;
	}
	if (ri->dir.y > 0)
	{
		ri->step.y = 1;
		ri->ray_len.y = ((ri->map_y + 1) * TILE_SIZE - pos.y) * ri->ray_step.y
			/ TILE_SIZE;
	}
	else
	{
		ri->step.y = -1;
		ri->ray_len.y = (pos.y - ri->map_y * TILE_SIZE) * ri->ray_step.y
			/ TILE_SIZE;
	}
}

void	draw_wall_strip(t_info *info, int x, double dist, t_point p)
{
	t_wall_info	wi;
	double		angle;

	angle = info->ray_angle;
	calculate_wall_dimensions(&wi, info, dist, angle);
	draw_wall_column(info, x, p, &wi);
}

void	calculate_step(t_ray_info *ri, double *dist, t_info *info)
{
	if (ri->ray_len.x < ri->ray_len.y)
	{
		ri->map_x += ri->step.x;
		*dist = ri->ray_len.x;
		ri->ray_len.x += ri->ray_step.x;
		if (ri->dir.x < 0)
			info->wall_side = 'W';
		else
			info->wall_side = 'E';
	}
	else
	{
		ri->map_y += ri->step.y;
		*dist = ri->ray_len.y;
		ri->ray_len.y += ri->ray_step.y;
		if (ri->dir.y < 0)
			info->wall_side = 'N';
		else
			info->wall_side = 'S';
	}
}

void	check_reset_player_angle(t_player *player)
{
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
}

double	raycast(t_point pos, double angle, t_vector *vector, t_info *info)
{
	t_ray_info	ri;
	double		dist;

	dist = 0;
	initialize_ray_direction(&ri, pos, angle);
	calculate_ray_length(&ri, pos);
	perform_dda(info, &ri, &dist);
	vector->start = pos;
	vector->end.x = (int)(pos.x + ri.dir.x * dist) % TILE_SIZE;
	vector->end.y = (int)(pos.y + ri.dir.y * dist);
	return (dist);
}
