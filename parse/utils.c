/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:53:46 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 03:57:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_init_map	*null_init(void)
{
    t_init_map  *init_data;

    init_data = gb_malloc(sizeof(t_init_map), 0);
	init_data->EA_tex = NULL;
	init_data->NO_tex = NULL;
	init_data->SO_tex = NULL;
	init_data->WE_tex = NULL;
	init_data->c_color = NULL;
	init_data->f_color = NULL;
	return (init_data);
}

t_morphed	*null_init2(t_init_map *data)
{
    t_morphed  *init_data;

    init_data = gb_malloc(sizeof(t_morphed), 0);
	init_data->EA_tex = ft_strdup(data->EA_tex);
	init_data->NO_tex = ft_strdup(data->NO_tex);
	init_data->SO_tex = ft_strdup(data->SO_tex);
	init_data->WE_tex = ft_strdup(data->WE_tex);
	init_data->c_num = NULL;
	init_data->f_num = NULL;
    init_data->map = NULL;
	return (init_data);
}

char *ft_trim_end(char *str, char *set)
{
    size_t  len;
    char    *newstr;

    if (str == NULL)
        return (NULL);
    len = ft_strlen(str);
    while (len > 0 && ft_strchr(set, str[len - 1]))
        len--;
    newstr = gb_malloc(len + 1, 0);
    if (newstr == NULL)
        return NULL;
    ft_strlcpy(newstr, str, len + 1);
    newstr[len + 1] = '\0';
    return (newstr);
}

bool    check_equal(char *s1, char *s2)
{
    int i;
    int j;

    if (s1[0] == '\0')
        return (false);
    i = 0;
    j = 0;
    while (s1[i] == ' ')
        i++;
    while (s1[i] && s2[j])
    {
        if (s1[i] != s2[j])
            return (false);
        i++;
        j++;
    }
    return (true);
}

bool    check_chars(char *s, char *set)
{
    int i;

    if (!s || !set)
        return (false);
    i = 0;
    while (s[i])
    {
        if (!ft_strchr(set, s[i]))
            return (false);
        i++;
    }
    return (true);
}

int biggest_line(t_list *map)
{
    int max;

    max = 0;
    while (map)
    {
        if (ft_strlen(map->content) >= max)
            max = ft_strlen(map->content);
        map = map->next;
    }
    return (max);
}


char    *morph_line(char *str, int len, char append)
{
    char    *res;
    int     i;

    if (ft_strlen(str) < len)
    {
        res = gb_malloc(sizeof(char) * len + 1, 0);
        i = 0;
        while (str[i])
        {
            res[i] = str[i];
            i++;
        }
        while (i < len)
            res[i++] = append;
        res[i] = '\0';
        free(str);
        return (ft_strdup(res));
    }
    return (str);
}