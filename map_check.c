/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 00:56:07 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/21 01:02:02 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	validate_tex(t_list *head, t_init_map *init_data)
{
	if (assign_line(head, init_data) == NULL)
	{
		print_err("Error\ntexture parsing error\n");
		free_data(init_data, NULL);
		exit(1);
	}
	if (check_tex(init_data) == false)
	{
		print_err("Error\ntexture parsing error\n");
		free_data(init_data, head);
		exit(1);
	}
}

t_tex_fd	*open_fd(t_list *map, t_init_map *map_tex)
{
	t_tex_fd	*refined_map;

	refined_map = malloc(sizeof(t_tex_fd));
	if (!refined_map)
		exit(1);
	refined_map->EA_fd = open(map_tex->EA_tex, O_RDONLY, 644);
	refined_map->SO_fd = open(map_tex->SO_tex, O_RDONLY, 644);
	refined_map->NO_fd = open(map_tex->NO_tex, O_RDONLY, 644);
	refined_map->WE_fd = open(map_tex->WE_tex, O_RDONLY, 644);
	refined_map->map = map;
	refined_map->f_num = convert_int(map_tex->f_color);
	refined_map->c_num = convert_int(map_tex->c_color);
	free(map_tex->c_color);
	free(map_tex->f_color);
	free(map_tex->EA_tex);
	free(map_tex->NO_tex);
	free(map_tex->SO_tex);
	free(map_tex->WE_tex);
	free(map_tex);
	return (refined_map);
}

bool	help_check(char *part, int mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (part[i] == ' ')
			i++;
		while (part[i])
		{
			if (part[i] != '1')
				return (false);
			i++;
		}
	}
	else if (mode == 1)
	{
		if (part[0] != '1' || part[ft_strlen(part) - 1] != '1')
			return (false);
	}
	
	return (true);
}

void	check_borders(t_list *map)
{
	bool	first;

	first  =true;
	while (map && map->content)
	{
		if (first || map->next == NULL)
		{
			if (!help_check(map->content, 0))
			{
				print_err("Error\ninvalid map\n");
				exit(1);
			}
			first = false;
		}
		else
		{
			if (!help_check(map->content, 1))
			{
				print_err("Error\ninvalid map\n");
				exit(1);
			}
		}
		map = map->next;
	}
}
