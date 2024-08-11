/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 03:47:01 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/11 06:35:53 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

mlx_texture_t	*open_tex(char *path)
{
	mlx_texture_t	*tex;

	tex = gb_malloc(sizeof(mlx_texture_t), 0);
	tex = mlx_load_png(path);
	if (!tex)
		write_fd("Error\nerror openning texture\n", 2);
	return (tex);
}

void	open_textures(t_data **all_data_adr)
{
	t_data	*all_data;

	all_data = *all_data_adr;
	all_data->no_texture = open_tex(all_data->no_tex);
	all_data->so_texture = open_tex(all_data->so_tex);
	all_data->ea_texture = open_tex(all_data->ea_tex);
	all_data->we_texture = open_tex(all_data->we_tex);
}

void	assign_player_pos(t_data **all_data_ptr)
{
	t_data	*all_data;
	int		i;
	int		j;
	char	**map;

	all_data = *all_data_ptr;
	map = all_data->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("SNWE", map[i][j]) != NULL)
			{
				all_data->player_x = j;
				all_data->player_y = i;
				all_data->player_face = map[i][j];
			}
			j++;
		}
		i++;
	}
}