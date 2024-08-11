/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:04 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/11 06:37:17 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/raycast.h"
#include "../inc/struct.h"
#include "../inc/utils.h"
#include "../inc/defines.h"

#include <stdio.h>
#include <math.h>

mlx_texture_t	*get_side_tex(char wall_side, t_data *data)
{
	if (wall_side == 'S')
		return (data->so_texture);
	else if (wall_side == 'N')
		return (data->no_texture);
	else if (wall_side == 'E')
		return (data->ea_texture);
	else if (wall_side == 'W')
		return (data->we_texture);
	return (NULL);
}

unsigned int	get_tex_pixel_color(t_point *point, t_info *info)
{
	//mlx_image_t		*img_tex;
	//mlx_texture_t	*tex;
	//int			val;
	//char		*tmp;
	//int			offset;
	(void)point;
	(void)info;

	//tex = get_side_tex(info->wall_side, info->data);
	//img_tex = tex->tex;

	//val = 0;
	//int y_offset = fmod(point->y, TILE_SIZE);
	//int x_offset = fmod(point->x, TILE_SIZE);
	////printf("x = %d, y = %d\n", x_offset, y_offset);
	//offset = ((int)y_offset * img_tex->line_length) + (int)x_offset;
	//tmp = &img_tex->addr[offset];
	//val = 0;
	//val = (*(tmp)) | (*(tmp + 1)) | *(tmp + 2);

	return 0;
}


