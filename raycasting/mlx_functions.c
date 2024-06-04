/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:52:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 01:59:41 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	close_window(t_mlx *mlx_ptr)
{
	mlx_destroy_window(mlx_ptr->mlx_srv, mlx_ptr->mlx_win);
	exit(0);
}

int	key_hook(int keycode, t_mlx *mlx_ptr)
{
	if (keycode == 53)
		close_window(mlx_ptr);
	return (0);
}

t_mlx	*init_mlx(t_morphed *map)
{
	t_mlx	*mlx_struct;
	t_data	*img;
	

	mlx_struct = gb_malloc(sizeof(t_mlx), 0);
	mlx_struct->mlx_srv = mlx_init();
	mlx_struct->mlx_win = mlx_new_window(mlx_struct->mlx_srv, X, Y, TITLE);
	if (!mlx_struct->mlx_srv || !mlx_struct->mlx_win)
	{
		write(2, "Error\nmlx init error\n", 22);
		exit(1);
	}
	img = gb_malloc(sizeof(t_data), 0);
	img->img = mlx_new_image(mlx_struct->mlx_srv, X, Y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	mlx_struct->img = img;
	mlx_struct->map = map;
	return (mlx_struct);
}

void	init_hooks(t_mlx *mlx_struct)
{
	mlx_key_hook(mlx_struct->mlx_win, &key_hook, mlx_struct);
	mlx_hook(mlx_struct->mlx_win, 17, 0, &close_window, mlx_struct);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
