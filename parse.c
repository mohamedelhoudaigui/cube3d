/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:55:30 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/22 18:59:46 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool    valid_file(int ac, char *file)
{
	int	len;

	if (ac != 2)
		return (false);
	if (ft_strlen(file) < 4)
	{
		print_err("Error\ninvalid arguments\n");
		exit (1);
	}
	len = ft_strlen(file) - 4;
	if (ft_strncmp(file + len, ".cub", 4) != 0)
	{
		print_err("Error\ninvalid arguments\n");
		exit (1);
	}
	if (open(file, O_RDONLY, 644) == -1)
	{
		print_err("Error\ninvalid arguments\n");
		exit (1);
	}
	return (true);
}



t_init_map	*assign_line(t_list *data, t_init_map *map)
{
	t_list		*map_list;
	t_list		*part;
	char		*tmp;

	if (!data || !map)
		return (NULL);
	while (data && data->content)
	{
		tmp = data->content;
		tmp = ft_strtrim(data->content, " ");
		if (analyse_line(tmp) == true)
		{
			if (ft_strncmp(tmp, "SO ", 3) == 0)
				map->SO_tex = tmp;
			else if (ft_strncmp(tmp, "NO ", 3) == 0)
				map->NO_tex = tmp;
			else if (ft_strncmp(tmp, "WE ", 3) == 0)
				map->WE_tex = tmp;
			else if (ft_strncmp(tmp, "EA ", 3) == 0)
				map->EA_tex = tmp;
			else if (ft_strncmp(tmp, "F ", 2) == 0)
				map->f_color = tmp;
			else if (ft_strncmp(tmp, "C ", 2) == 0)
				map->c_color = tmp;
		}
		data = data->next;
	}
	return (map);
}

t_list	*fill_map(char *file)
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

t_list	*isolate_map(t_list *head)
{
	int		i;
	char	*tmp;
	t_list	*part;
	t_list	*map;
	bool	key;

	map = NULL;
	key = false;
	while (head && head->content)
	{
		i = 0;
		tmp = head->content;
		while (tmp[i] && tmp[i] == ' ')
			i++;
		if (key == true && tmp[i] == '\n' && tmp[i + 1] == '\0')
		{
			print_err("Error\nnew line in map\n");
			exit(1);
		}
		if (tmp[i] && (tmp[i] == '0' || tmp[i] == '1'))
		{
			key = true;
			tmp = replace(&tmp, "\n");
			part = ft_lstnew(tmp);
			ft_lstadd_back(&map, part);
		}
		head = head->next;
	}
	return (map);
}	

void	f()
{
	system("leaks cub3D");
}

int main(int ac, char **av)
{
	// atexit(f);
	t_list		*head;
	t_list		*map;
	t_init_map	*init_data;
	t_tex_fd	*refined_map;
	char		**map_char;

	valid_file(ac, av[1]);
	head = fill_map(av[1]);
	init_data = ft_calloc(sizeof(t_init_map), 1);
	validate_tex(head, init_data);
	map = isolate_map(head);
	refined_map = open_fd(init_data);
	check_borders(map);
	check_map_elements(map);
	map_char = transfer_map(map);
	free(map);
	refined_map->map = map_char;
	print_struct(refined_map);
	exit (0);
}
