/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:50:47 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 20:24:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"

void	set_player_position(t_info *info, int i, int j)
{
	info->player->vector.start.x = i * TILE_SIZE + TILE_SIZE / 2;
	info->player->vector.start.y = j * TILE_SIZE + TILE_SIZE / 2;
}

void	set_player_angle(t_info *info, char direction)
{
	if (direction == 'E')
		info->player->angle = 0;
	else if (direction == 'S')
		info->player->angle = M_PI / 2;
	else if (direction == 'W')
		info->player->angle = M_PI;
	else if (direction == 'N')
		info->player->angle = 3 * M_PI / 2;
}

void	process_map_tile(t_info *info, char **map, int i, int j)
{
	if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W'
		|| map[j][i] == 'E')
	{
		set_player_position(info, i, j);
		set_player_angle(info, map[j][i]);
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
			process_map_tile(info, map, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}
