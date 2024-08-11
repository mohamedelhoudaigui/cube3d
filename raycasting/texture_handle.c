/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:04 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/11 23:23:23 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include <math.h>
#include <stdio.h>

t_texture	*get_side_tex(char wall_side, t_data *data)
{
	if (wall_side == 'S')
		return (data->so_texture);
	else if (wall_side == 'N')
		return (data->no_texture);
	else if (wall_side == 'E')
		return (data->ea_texture);
	return (data->we_texture);
}

unsigned int	get_tex_pixel_color(int y2, t_point *point, t_info *info,
		int x2)
{
	t_texture		*tex;
	t_img			*img_tex;
	int				x;
	char			*pixels;
	int				offset;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned int	color;

	tex = get_side_tex(info->wall_side, info->data);
	img_tex = tex->tex;
	pixels = mlx_get_data_addr(img_tex, &img_tex->bits_per_pixel,
			&img_tex->line_length, &img_tex->endian);
	x = (int)fmod(point->x, TILE_SIZE);
	y2 = (y2 * 64) / 100;
	offset = (y2 * TILE_SIZE + x2) * (img_tex->bits_per_pixel / 8);
	return ((pixels[offset + 2] << 16) | (pixels[offset] << 8) | pixels[offset]);
}
