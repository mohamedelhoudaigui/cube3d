
#include "../inc/defines.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// double  angle_add(double angle, double angle_to_add)
// {
//     double new_angle = (angle + angle_to_add) ;
//     new_angle = new_angle % 360.0;
//
//     return (new_angle);
// }

void	fill_image(t_info *info, int color)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = 0;
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
void	draw_wall_strip(t_info *info, int x, double dist, double angle, int x2)
{
	t_img	*image;
	t_point	point;
	int		color;
	double	corrected_dist;
	double	wall_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		y2;

	image = &info->img;
	corrected_dist = dist * cos(angle - info->player->angle);
	wall_height = (SCREEN_HEIGHT / corrected_dist) * TILE_SIZE;
	info->wall_h = wall_height;
	draw_start = (SCREEN_HEIGHT - wall_height) / 2;
	// if (draw_start < 0)
	//  return ;
	draw_end = (SCREEN_HEIGHT + wall_height) / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	info->dis = corrected_dist;
	info->wall_h = wall_height;
	info->draw_start = draw_start;
	info->draw_end = draw_end;
	// if (info->wall_side == 'N') {
	//  color = 0xFF0000;
	//} else if (info->wall_side == 'S') {
	//  color = 0x00FF00;
	//} else if (info->wall_side == 'E') {
	//  color = 0x0000FF;
	//} else if (info->wall_side == 'W') {
	//  color = 0xFFFF00;
	//} else {
	//  color = 0xFFFFFF;
	//}
	point.x = x;
	y = draw_start;
	while (y <= draw_end)
	{
		y2 = ((y - draw_start) * 100) / wall_height;
		point.y = y;
		if (y < 0 || y > SCREEN_HEIGHT)
		{
			y++;
			continue ;
		}
		color = get_tex_pixel_color(y2, &point, info, x2);
		put_pixel(image, point, color);
		y++;
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

void	clear_image(t_info *info)
{
	t_img	*image;
	t_point	point;

	image = &info->img;
	point.x = 0;
	point.y = 0;
	while (point.y < SCREEN_HEIGHT)
	{
		while (point.x < SCREEN_WIDTH)
		{
			put_pixel(image, point, 0);
			point.x += 1;
		}
		point.x = 0;
		point.y += 1;
	}
}

void	render_map(t_info *info)
{
	t_img	*image;
	t_point	point;
	char	**map;
	int		y;
	int		x;
	int		dy;
	int		dx;

	image = &info->img;
	map = info->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				dy = 0;
				while (dy < MAP_TILE_SIZE)
				{
					dx = 0;
					while (dx < MAP_TILE_SIZE)
					{
						point.x = x * MAP_TILE_SIZE + dx;
						point.y = y * MAP_TILE_SIZE + dy;
						put_pixel(image, point, COLOR);
						dx++;
					}
					dy++;
				}
			}
			else
			{
				point.x = info->player->vector.start.x / MAP_TILE_SIZE;
				point.y = info->player->vector.start.y / MAP_TILE_SIZE;
				put_pixel(image, point, GREEN);
			}
			x++;
		}
		y++;
	}
}

void	set_player_spawn(t_info *info)
{
	char	**map;
	int		i;
	int		j;

	map = info->map;
	i = 0;
	j = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W'
				|| map[j][i] == 'E')
			{
				info->player->vector.start.x = i * TILE_SIZE + TILE_SIZE / 2;
				info->player->vector.start.y = j * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
}
double	raycast(t_point pos, double angle, t_vector *vector, t_info *info)
{
	t_point	dir;
	t_point	ray_step;
	int		map_x;
	int		map_y;
	t_point	ray_len;
	t_point	step;
	char	**map;
	int		hit;
	double	dist;
	int		end_x;
	int		end_y;

	dir.x = cos(angle);
	dir.y = sin(angle);
	ray_step.x = fabs(TILE_SIZE / dir.x);
	ray_step.y = fabs(TILE_SIZE / dir.y);
	map_x = (int)(pos.x / TILE_SIZE);
	map_y = (int)(pos.y / TILE_SIZE);
	map = info->map;
	if (dir.x < 0)
	{
		step.x = -1;
		ray_len.x = (pos.x - map_x * TILE_SIZE) * ray_step.x / TILE_SIZE;
	}
	else
	{
		step.x = 1;
		ray_len.x = ((map_x + 1) * TILE_SIZE - pos.x) * ray_step.x / TILE_SIZE;
	}
	if (dir.y > 0)
	{
		step.y = 1;
		ray_len.y = ((map_y + 1) * TILE_SIZE - pos.y) * ray_step.y / TILE_SIZE;
	}
	else
	{
		step.y = -1;
		ray_len.y = (pos.y - map_y * TILE_SIZE) * ray_step.y / TILE_SIZE;
	}
	hit = 0;
	dist = 0;
	while (!hit && map_x >= 0 && map_y >= 0)
	{
		if (ray_len.x < ray_len.y)
		{
			map_x += step.x;
			dist = ray_len.x;
			ray_len.x += ray_step.x;
			info->wall_side = (dir.x < 0) ? 'W' : 'E';
		}
		else
		{
			map_y += step.y;
			dist = ray_len.y;
			ray_len.y += ray_step.y;
			info->wall_side = (dir.y < 0) ? 'N' : 'S';
		}
		if (map_x >= 0 && map_y >= 0)
		{
			if (map[map_y][map_x] != '0' && map[map_y][map_x] != 'N'
				&& map[map_y][map_x] != 'S' && map[map_y][map_x] != 'W'
				&& map[map_y][map_x] != 'E')
			{
				hit = 1;
			}
		}
	}
	end_x = pos.x + dir.x * dist;
	end_x = end_x % TILE_SIZE;
	end_y = pos.y + dir.y * dist;
	vector->start = pos;
	vector->end.x = end_x;
	vector->end.y = end_y;
	return (dist);
}

void	test_cast(t_info *info)
{
	t_player	*player;
	double		dist;
	t_vector	vector;
	double		fov;
	int			x;
	double		ray_angle;

	if (info->player->vector.len == -1)
	{
		set_player_spawn(info);
		info->player->vector.len = -2;
	}
	player = info->player;
	clear_image(info);
	put_floor_color(info, info->data->color_f);
	put_skye_color(info, info->data->color_c);
	// preload both funcs in images and just out them at first.
	fov = player->fov;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = player->angle - fov / 2 + (x / (double)SCREEN_WIDTH) * fov;
		dist = raycast(info->player->vector.start, ray_angle, &vector, info);
		draw_wall_strip(info, x, dist, ray_angle, vector.end.x);
		x++;
	}
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
}
