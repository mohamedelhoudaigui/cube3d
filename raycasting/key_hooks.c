/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 02:37:59 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 07:45:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    move_right(t_mlx *mlx_struct)
{
	mlx_struct->angle = -45;
}

void    move_left(t_mlx *mlx_struct)
{
	mlx_struct->angle = 135;
}

void    move_down(t_mlx *mlx_struct)
{
	mlx_struct->angle = 45;
}

void    move_up(t_mlx *mlx_struct)
{
	mlx_struct->angle = -135;
}

void	move_w(t_mlx *mlx_struct)
{
	char    **map;
	int     *pos;

	map = mlx_struct->map->map;
	pos = get_player_pos(map);
	if (map[pos[0] - 1][pos[1]] == '0')
	{
		map[pos[0] - 1][pos[1]] = map[pos[0]][pos[1]];
		map[pos[0]][pos[1]] = '0';
	}
}

void	move_s(t_mlx *mlx_struct)
{
	char    **map;
	int     *pos;

	map = mlx_struct->map->map;
	pos = get_player_pos(map);
	if (map[pos[0] + 1][pos[1]] == '0')
	{
		map[pos[0] + 1][pos[1]] = map[pos[0]][pos[1]];
		map[pos[0]][pos[1]] = '0';
	}
}

void	move_a(t_mlx *mlx_struct)
{
	char    **map;
	int     *pos;

	map = mlx_struct->map->map;
	pos = get_player_pos(map);
	if (map[pos[0]][pos[1] - 1] == '0')
	{
	    map[pos[0]][pos[1] - 1] = map[pos[0]][pos[1]];
	    map[pos[0]][pos[1]] = '0';
	}
}

void	move_d(t_mlx *mlx_struct)
{
	char    **map;
	int     *pos;

	map = mlx_struct->map->map;
	pos = get_player_pos(map);
	if (map[pos[0]][pos[1] + 1] == '0')
	{
		map[pos[0]][pos[1] + 1] = map[pos[0]][pos[1]];
		map[pos[0]][pos[1]] = '0';
	}
}

int	key_hook(int keycode, t_mlx *mlx_struct)
{
	if (keycode == 53)
		close_window(mlx_struct);
	if (keycode == 124)
		move_d(mlx_struct);
	if (keycode == 125)
		move_s(mlx_struct);
	if (keycode == 126)
		move_w(mlx_struct);
	if (keycode == 123)
		move_a(mlx_struct);
	if (keycode == 2)
		move_right(mlx_struct);
	if (keycode == 1)
		move_down(mlx_struct);
	if (keycode == 0)
		move_left(mlx_struct);
	if (keycode == 13)
		move_up(mlx_struct);
	draw_map(mlx_struct);
	return (0);
}
