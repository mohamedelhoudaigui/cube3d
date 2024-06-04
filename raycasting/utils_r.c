/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 02:45:15 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 02:55:42 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int *get_player_pos(char **map)
{
    int i;
    int j;
    int *pos;
    
    i = 0;
    pos = gb_malloc(sizeof(int) * 2, 0);
    while (i < ft_doubleptr_size(map))
    {
        j = 0;
        while (j < ft_strlen(map[0]))
        {
            if (ft_strchr("SNWE", map[i][j]))
            {
                pos[0] = i;
                pos[1] = j;
            }
            j++;
        }
        i++;
    }
    return (pos);
}
