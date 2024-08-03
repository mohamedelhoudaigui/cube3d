/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:12 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/03 15:15:53 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*map_data;

	if (ac != 2)
		write_fd("Error\nerror args\n", 2);
	map = parse(av[1]);
	validate(&map);
	map_data = transform(&map);
	check_textures(&map_data);
	//printf("%s\n", map_data->no_tex);
	//printf("%s\n", map_data->so_tex);
	//printf("%s\n", map_data->ea_tex);
	//printf("%s\n", map_data->we_tex);
	//printf("%X\n", map_data->color_c);
	//printf("%X\n", map_data->color_f);
	//char **gg = map_data->map;
	//int	i = 0;
	//while (gg[i++])
	//	printf("%s\n", gg[i]);

	exit(0);
}