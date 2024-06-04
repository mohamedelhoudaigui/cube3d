/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 06:22:21 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/04 06:22:51 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int get_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

int get_char_color(char map_char)
{
    int color;

    switch (map_char)
    {
        case '1' : 
            color = get_color(205, 92, 92);
            break ;
        case '0' :
            color = get_color(255, 255, 255);
            break ;
        case ' ' :
            color = get_color(0, 0, 0);
            break ;
        case '.':
            color = get_color(0, 128, 0);
            break ;
        default :
            color = get_color(240, 230, 140);
            break ;
    }
    return (color);
}