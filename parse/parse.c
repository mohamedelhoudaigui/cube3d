/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:55:30 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 09:21:27 by mel-houd         ###   ########.fr       */
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

char	**alter_map(t_init_map *init_data)
{
	char	**res;
	t_list	*data;
	int		i;
	int		len;

	data = init_data->map;
	res = gb_malloc(sizeof(char *) * ft_lstsize(data) + 1, 0);
	i = 0;
	len = biggest_line(data);
	while (data)
	{
		res[i] = morph_line(data->content, len, ' ');
		i++;
		data = data->next;
	}
	res[i] = NULL;
	return (res);
}

bool	check_line(char *s, int mode)
{
	int	i;
	
	i = 0;
	if (mode == 0)
	{
		while (s[i])
		{
			if (s[i] != ' ' && s[i] != '1')
				return (false);
			i++;
		}
		return (true);	
	}
	while (s[i])
	{
		if (ft_strchr("SNWE01 ", s[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

bool	check_map_elements(char **map)
{
	bool	player;
	int		mode;
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		if (i == 0 || i == ft_doubleptr_size(map) - 1)
			mode = 0;
		else
			mode = 1;
		if (!check_line(map[i], mode))
		{
			write(2, "Error\nmap elements error\n", 25);
			exit(1);
		}
		if (ft_strchr(map[i], 'N') || ft_strchr(map[i], 'W')
			|| ft_strchr(map[i], 'E') || ft_strchr(map[i], 'S'))
		{
			player = true;
		}
		i++;
	}
	if (!player)
	{
		write(2, "Error\nno player error\n", 22);
		exit(1);
	}
	return (true);
}

bool	check_borders(char **map)
{
	int		x;
	int		y;
	int		max_x;
	int		max_y;
	bool	border;

	y = 1;
	max_x = ft_strlen(map[0]) - 1;
	max_y = ft_doubleptr_size(map) - 1;
	border = true;
	while (y < max_y)
	{
		x = 1;
		while (x < max_x)
		{
			if (map[y][x] == ' ')
			{
				if (!ft_strchr(" 1", map[y - 1][x]))
					border = false;
				if (!ft_strchr(" 1", map[y + 1][x]))
					border = false;
				if (!ft_strchr(" 1", map[y][x - 1]))
					border = false;
				if (!ft_strchr(" 1", map[y][x + 1]))
					border = false;
			}
			x++;
		}
		y++;
	}
	if (!border)
	{
		write(2, "Error\nborder error\n", 19);
		exit(1);
	}
	return (true);
}

void	print_morphed(t_morphed *data)
{
	int	i;

	printf("%s\n", data->EA_tex);
	printf("%s\n", data->WE_tex);
	printf("%s\n", data->NO_tex);
	printf("%s\n", data->SO_tex);
	printf("c color = %d %d %d\n", data->c_num[0], data->c_num[1], data->c_num[2]);
	printf("f color = %d %d %d\n", data->f_num[0], data->f_num[1], data->f_num[2]);
	i = 0;
	while (data->map[i])
		printf("%s\n", data->map[i++]);	
}

t_morphed	*parse(int ac, char **av)
{
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
	map_char = alter_map(init_data);
	refined_map->map = map_char;
	check_map_elements(refined_map->map);
	check_borders(refined_map->map);
	print_morphed(refined_map);
	return (refined_map);
}
