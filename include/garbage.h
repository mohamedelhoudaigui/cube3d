/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:17:29 by mel-houd          #+#    #+#             */
/*   Updated: 2024/03/06 00:59:29 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H

# define GARBAGE_H

# include <stdlib.h>

typedef struct s_garb
{
	void			*addr;
	struct s_garb	*next;
}				t_garb ;

void	clear_list(t_garb *list);
void	add_node(t_garb **list, t_garb *node);
void	*gb_malloc(size_t size, int type);

#endif
