/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:52:27 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/02 09:39:24 by mel-houd         ###   ########.fr       */
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

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx_struct;

	mlx_struct = gb_malloc(sizeof(t_mlx), 0);
	mlx_struct->mlx_srv = mlx_init();
	mlx_struct->mlx_win = mlx_new_window(mlx_struct->mlx_srv, X, Y, TITLE);
	if (!mlx_struct->mlx_srv || !mlx_struct->mlx_win)
	{
		print_err("Error\nmlx init error\n");
		exit(1);
	}
	return (mlx_struct);
}

void	init_hooks(t_mlx *mlx_struct)
{
	mlx_key_hook(mlx_struct->mlx_win, &key_hook, mlx_struct);
	mlx_hook(mlx_struct->mlx_win, 17, 0, &close_window, mlx_struct);
}
