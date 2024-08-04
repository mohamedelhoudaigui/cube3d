/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:01:12 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/04 14:06:54 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse/cub.h"

void	check_extention(char *buffer, char *ext)
{
	int	size_ext;
	int	size;

	size = ft_strlen(buffer) - 1;
	size_ext = ft_strlen(ext) - 1;
	if (size_ext >= size)
		write_fd("Error\nfile name error\n", 2);
	while (ext[size_ext] == buffer[size])
	{
		size_ext--;
		size--;
	}
	if (size_ext != -1)
		write_fd("Error\nfile name error\n", 2);
}

t_data	*parse_entry(int ac, char **av)
{
	t_map	*map;
	t_data	*map_data;

	if (ac != 2)
		write_fd("Error\nerror args\n", 2);
	check_extention(av[1], ".cub");
	map = parse(av[1]);
	validate(&map);
	map_data = transform(&map);
	//check_textures(&map_data);
	return (map_data);
}



int	main(int ac, char **av)
{
	t_data	*map_data;
	int		i;
	char	**gg;

	map_data = parse_entry(ac, av);
	printf("%s\n", map_data->no_tex);
	printf("%s\n", map_data->so_tex);
	printf("%s\n", map_data->ea_tex);
	printf("%s\n", map_data->we_tex);
	printf("%X\n", map_data->color_c);
	printf("%X\n", map_data->color_f);
	gg = map_data->map;
	i = 0;
	while (gg[i])
	{
		printf("%s\n", gg[i]);
		i++;
	}
	return (0);
}

// duplicated textures error
