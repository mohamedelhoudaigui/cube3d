/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 03:47:01 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/06 03:59:17 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	*open_tex(char *path, void *mlx_ptr)
{
	t_texture	*tex;

	tex= gb_malloc(sizeof(t_texture), 0);
	tex->tex = mlx_xpm_file_to_image(mlx_ptr, path, &tex->w, &tex->h);
	if (!tex->tex)
		write_fd("Error\nerror openning texture\n", 2);
	return (tex);
}

void	open_textures(t_data **all_data_adr)
{
	t_data	*all_data;

	all_data = *all_data_adr;
	all_data->no_texture = open_tex(all_data->no_tex, all_data->ini->mlx);
	all_data->so_texture = open_tex(all_data->so_tex, all_data->ini->mlx);
	all_data->ea_texture = open_tex(all_data->ea_tex, all_data->ini->mlx);
	all_data->we_texture = open_tex(all_data->we_tex, all_data->ini->mlx);
}