/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:36:20 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 09:24:05 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void    f()
{
    system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_morphed	*full_map;
	t_mlx		*mlx_struct;

	full_map = parse(ac, av);
	print_morphed(full_map);
	
	mlx_struct = init_mlx();
    init_hooks(mlx_struct);
    mlx_loop(mlx_struct->mlx_srv);
    exit(0);
}