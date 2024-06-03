/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubleptr_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:25:33 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 08:26:34 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_doubleptr_size(char **s)
{
    int i;

    if (!s)
        return (-1);
    i = 0;
    while (s[i])
        i++;
    return (i);
}
