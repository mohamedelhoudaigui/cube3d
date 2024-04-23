/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:36:20 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/23 18:39:55 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	f()
{
	system("leaks cub3D");
}

t_mlx	*init_mlx()
{
	
}

int	main(int ac, char **av)
{
	atexit(f);
	t_tex_fd	*full_map;
	t_mlx		*mlx_struct;

	full_map = parse(ac, av);
	mlx_struct = init_mlx();
	return (0);
}