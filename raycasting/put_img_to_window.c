/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:30:06 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/05 02:31:03 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    put_img(t_mlx *mlx_struct, t_data *chosen_img)
{
    mlx_clear_window(mlx_struct->mlx_srv, mlx_struct->mlx_win);
	mlx_put_image_to_window(mlx_struct->mlx_srv, mlx_struct->mlx_win, chosen_img->img, 0, 0);
}
