/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:55:30 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 04:09:01 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_list	*from_file(char *file_name, t_list **head)
{
	int		fd;
	char	*tmp;
	t_list	*node;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nerror opening map!", 25);
		exit(1);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (*head);
		node = ft_lstnew(ft_trim_end(tmp, " \n"));
		ft_lstadd_back(head, node);
		free(tmp);
	}
	return (*head);
}

void	assign_lines(t_list *head, t_init_map **init_data_p)
{
	t_init_map	*init_data;
	t_list		*map;
	t_list		*node;

	init_data = *init_data_p;
	while (head)
	{
		if (check_equal(head->content, "NO ") == true)
		{
			init_data->NO_tex = ft_strdup(head->content);
		}
		else if (check_equal(head->content, "SO ") == true)
			init_data->SO_tex = ft_strdup(head->content);
		else if (check_equal(head->content, "WE ") == true)
			init_data->WE_tex = ft_strdup(head->content);
		else if (check_equal(head->content, "EA ") == true)
			init_data->EA_tex = ft_strdup(head->content);
		else if (check_equal(head->content, "F ") == true)
			init_data->f_color = ft_strdup(head->content);
		else if (check_equal(head->content, "C ") == true)
			init_data->c_color = ft_strdup(head->content);
		else if (check_equal(head->content, "1") || check_equal(head->content, "0"))
			break ;
		head = head->next;
	}
	if (!init_data->SO_tex || !init_data->EA_tex || !init_data->WE_tex
		|| !init_data->NO_tex || !init_data->c_color || !init_data->f_color)
	{
		write(2, "Error\nmap misplaced\n", 20);
		exit(1);
	}
	map = NULL;
	while (head)
	{
		if ((!check_equal(head->content, "1") && !check_equal(head->content, "0")) || !check_chars(head->content, " 01NSEW"))
		{
			write(2, "Error\nmap line error\n", 20);
			exit(1);
		}
		node = ft_lstnew(ft_strdup(head->content));
		ft_lstadd_back(&map, node);
		head = head->next;
	}
	init_data->map = map;
}

int	*extract_color(char *color)
{
	char	*tmp;
	int		*res;
	char	**split;
	int		i;

	tmp = ft_strtrim(color, "[] FC");
	res = gb_malloc(sizeof(int) * 3, 0);
	split = ft_split(tmp, ", ");
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > 3 || ft_allnum(split[i]) == false)
		{
			write(2, "Error\ncolor are from 0 to 255\n", 30);
			exit(1);
		}
		i++;
	}
	res[0] = ft_atoi(split[0]);
	res[1] = ft_atoi(split[1]);
	res[2] = ft_atoi(split[2]);
	i = 0;
	while (i < 3)
	{
		if (res[i] < 0 || res[i] > 255)
		{
			write(2, "Error\ncolor are from 0 to 255\n", 30);
			exit(1);
		}
		i++;
	}
	return (res);
}

void	assign_color(t_init_map *init_data, t_morphed *refined_map)
{
	refined_map->f_num = extract_color(init_data->f_color);
	refined_map->c_num = extract_color(init_data->c_color);
}

// void	check_map_borders(t_morphed *refined_map)
// {
// 	char	**map;
// 	int		len;
// 	int		i;
// 	int		j;

// 	map = refined_map->map;
// 	len = 0;
// 	while (map[len])
// 		len++;
// 	i = 0;
// 	while (map[i])
// 	{
// 		if (i == 0 || i == len - 1)
// 		{
// 			if (!check_chars(map[i], " 1"))
// 			{
// 				write(2, "Error\nerror in line 0 or len - 1\n", 33);
// 				exit(1);
// 			}
// 		}
// 		else
// 		{
// 			j = 0;
// 			while (map[i][j] == ' ')
// 				j++;
// 			if (map[i][j] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
// 			{
// 				write(2, "Error\nborder error\n", 19);
// 				exit(1);
// 			}
// 			while (map[i][j])
// 			{
				
// 			}
// 		}
// 	}
// }






void	print_tex(t_morphed *texs)
{
	t_list *map;

	// printf("%s\n", texs->SO_tex);
	// printf("%s\n", texs->EA_tex);
	// printf("%s\n", texs->WE_tex);
	// printf("%s\n", texs->NO_tex);
	map = texs->map;
	while (map)
	{
		printf("%p\n", map->content);
		map = map->content;
	}	
}

void	f()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	// atexit(f);
	t_list		*head;
	t_list		*map;
	char		**map_char;
	t_init_map	*init_data;
	t_morphed	*refined_map;

	if (ac != 2)
	{
		write(2, "Error\nargs error\n", 17);
		exit(1);
	}
	head = from_file(av[1], &head);
	init_data = null_init();
	assign_lines(head, &init_data);
	refined_map = null_init2(init_data);
	assign_color(init_data, refined_map);
	
	return (0);
}
