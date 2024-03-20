/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:55:30 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/20 04:57:56 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void    arg_err(void)
{
	write(2, "invalid arguments\n", 18);
}

bool    valid_file(int ac, char *file)
{
	int	len;

	if (ac != 2)
		return (false);
	if (ft_strlen(file) < 4)
		return (false);
	len = ft_strlen(file) - 4;
	if (ft_strncmp(file + len, ".cub", 4) != 0)
		return (false);
	if (open(file, O_RDONLY, 644) == -1)
		return (false);
	return (true);
}

t_init_map	*assign_line(t_list *data)
{
	t_list		*map_list;
	t_init_map	*map;
	t_list		*part;

	if (!data)
		return (NULL);
	map = gb_malloc(sizeof(t_init_map), 0);
	map->map = NULL;
	while (data && data->content)
	{
		if (ft_strncmp(data->content, "SO ", 3) == 0)
			map->SO_tex = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "NO ", 3) == 0)
			map->NO_tex = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "WE ", 3) == 0)
			map->WE_tex = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "EA ", 3) == 0)
			map->EA_tex = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "F ", 2) == 0)
			map->f_color = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "C ", 2) == 0)
			map->c_color = ft_strdup(data->content);
		else if (ft_strncmp(data->content, "1", 1) == 0
				|| ft_strncmp(data->content, "0", 1) == 0)
			{
				part = ft_lstnew(data->content);
				ft_lstadd_back(&map->map, part);
			}
		else
			return (NULL);
		data = data->next;
	}
	return (map);
}

t_list	*parse_map(char *file)
{
	int		fd;
	char	*line;
	t_list	*data;
	t_list	*part;

	data = NULL;
	fd = open(file, O_RDONLY, 777);
	line = get_next_line(fd);
	while (line != NULL)
	{
		part = ft_lstnew(line);
		ft_lstadd_back(&data, part);
		line = get_next_line(fd);
	}
	return (data);
}

int main(int ac, char **av)
{
	t_list		*head;
	t_init_map	*init_data;
	t_list		*map;

	if (valid_file(ac, av[1]) == false)
	{
		arg_err();
		return (1);
	}
	head = parse_map(av[1]);
	if (!head)
	{
		gb_malloc(0, 1);
		return (1);
	}
	init_data = assign_line(head);
	if (!init_data)
	{
		gb_malloc(0, 1);
		return (1);
	}
	
	return (0);
}
