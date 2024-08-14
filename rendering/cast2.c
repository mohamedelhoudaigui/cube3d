/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:03:24 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 20:24:00 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

void	initialize_ray_direction(t_ray_info *ri, t_point pos, double angle)
{
	ri->dir.x = cos(angle);
	ri->dir.y = sin(angle);
	ri->ray_step.x = fabs(TILE_SIZE / ri->dir.x);
	ri->ray_step.y = fabs(TILE_SIZE / ri->dir.y);
	ri->map_x = (int)(pos.x / TILE_SIZE);
	ri->map_y = (int)(pos.y / TILE_SIZE);
}

void	put_skye_color(t_info *info, int color)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = 0;
	while (point.y < SCREEN_HEIGHT / 2)
	{
		while (point.x < SCREEN_WIDTH)
		{
			put_pixel(image, point, color);
			point.x += 1;
		}
		point.x = 0;
		point.y += 1;
	}
}

void	put_floor_color(t_info *info, int color)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = SCREEN_HEIGHT / 2;
	while (point.y < SCREEN_HEIGHT)
	{
		while (point.x < SCREEN_WIDTH)
		{
			put_pixel(image, point, color);
			point.x += 1;
		}
		point.x = 0;
		point.y += 1;
	}
}

void	draw_wall_column(t_info *info, int x, t_point p, t_wall_info *wi)
{
	t_img	*image;
	t_point	point;
	int		y2;
	int		color;
	int		y;

	image = &info->img;
	point.x = x;
	y = wi->draw_start;
	while (y <= wi->draw_end)
	{
		y++;
		if (y < 0 || y >= SCREEN_HEIGHT)
			continue ;
		y2 = ((y - wi->draw_start) * 100) / wi->wall_height;
		point.y = y;
		color = get_tex_pixel_color(y2, info, p);
		put_pixel(image, point, color);
	}
}

void	calculate_wall_dimensions(t_wall_info *wi, t_info *info, double dist,
		double angle)
{
	wi->corrected_dist = dist * cos(angle - info->player->angle);
	wi->wall_height = (SCREEN_HEIGHT / wi->corrected_dist) * TILE_SIZE;
	wi->draw_start = (SCREEN_HEIGHT - wi->wall_height) / 2;
	wi->draw_end = (SCREEN_HEIGHT + wi->wall_height) / 2 - 5;
	if (wi->draw_end >= SCREEN_HEIGHT)
		wi->draw_end = SCREEN_HEIGHT - 1;
	info->dis = wi->corrected_dist;
	info->wall_h = wi->wall_height;
	info->draw_start = wi->draw_start;
	info->draw_end = wi->draw_end;
}
