/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 23:59:20 by mel-houd          #+#    #+#             */
/*   Updated: 2024/04/22 01:33:46 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_struct(t_tex_fd *tex)
{
	t_list	*map;

	printf("%d\n", tex->EA_fd);
	printf("%d\n", tex->WE_fd);
	printf("%d\n", tex->SO_fd);
	printf("%d\n", tex->EA_fd);
	printf("[%d %d %d]\n", tex->c_num[0], tex->c_num[1], tex->c_num[2]);
	printf("[%d %d %d]\n", tex->f_num[0], tex->f_num[1], tex->f_num[2]);
	map = tex->map;
	while (map && map->content)
	{
		printf("%s\n", map->content);
		map = map->next;
	}
}

void	print_err(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
}

bool	analyse_line(char *tmp)
{
	if (tmp[0] == '\n' && tmp[1] == '\0')
		return (false);
	return (true);
}

char	*replace(char **p_holder, char *set)
{
	char	*tmp;

	tmp = ft_strtrim(*p_holder, set);
	free(*p_holder);
	return (tmp);
}

bool check_tex(t_init_map *map)
{
    if (!map->c_color
        || !map->f_color
        || !map->EA_tex
        || !map->NO_tex
        || !map->SO_tex
        || !map->WE_tex)
    {
        return (false);
    }
    map->c_color = replace(&map->c_color, "C \n");
    map->f_color = replace(&map->f_color, "F \n");
    map->EA_tex = replace(&map->EA_tex, "EA \n");
    map->SO_tex = replace(&map->SO_tex, "SO \n");
    map->NO_tex = replace(&map->NO_tex, "NO \n");
    map->WE_tex = replace(&map->WE_tex, "WE \n");
    return (true);
}

void	free_data(t_init_map *map, t_list *data)
{
	t_list	*map_p;

	free(map->c_color);
	free(map->f_color);
	free(map->SO_tex);
	free(map->WE_tex);
	free(map->NO_tex);
	free(map->EA_tex);
	if (data)
		ft_lstclear(&data, &free);
}

int	*convert_int(char *numb)
{
	char	**split;
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * 3);
	split = ft_split(numb, " ,");
	if (!arr || !split)
		exit(1);
	i = 0;
	while (i < 3)
	{
		arr[i] = ft_atoi(split[i]);
		i++;
	}
	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
	return (arr);
}
