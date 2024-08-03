/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:40:51 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/03 04:41:55 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strchr(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}


int	ft_atoi(char *str)
{
	int					i;
	long long	res;
	int					sign;

	i = 0, res = 0, sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -sign;
		i++;
	}
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (str[i++] - '0') + (res * 10);
	res *= sign;
	res > (long long)INT_MAX ? res = INT_MAX : 1;
	res < (long long)INT_MIN ? res = INT_MIN : 1;
	return ((int)res);
}