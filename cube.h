/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:52:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/03 03:57:48 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include "./include/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <mlx.h>

# define X 600
# define Y 600
# define TITLE "cub3D"

typedef	struct	s_morphed
{
	char	*NO_tex;
	char	*SO_tex;
	char	*WE_tex;
	char	*EA_tex;
	int		*f_num;
	int		*c_num;
	t_list	*map;
}				t_morphed;

typedef struct s_init_map
{
	char	*NO_tex;
	char	*SO_tex;
	char	*WE_tex;
	char	*EA_tex;
	char	*f_color;
	char	*c_color;
	t_list	*map;
}				t_init_map;

//-----------------------------------

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef	struct s_mlx
{
	void	*mlx_srv;
	void	*mlx_win;
}				t_mlx;

//----------parsing headers :

t_morphed	*parse(int ac, char **av);
t_init_map	*null_init(void);
char		*ft_trim_end(char *str, char *set);
bool    	check_equal(char *s1, char *s2);
void		assign_lines(t_list *head, t_init_map **init_data_p);
t_list		*from_file(char *file_name, t_list **head);
t_morphed	*null_init2(t_init_map *data);
bool    	check_chars(char *s, char *set);
int			biggest_line(t_list *map);
char   	 	*morph_line(char *str, int len, char append);

//------------raycasting headers :
t_mlx	*init_mlx(void);
int		key_hook(int keycode, t_mlx *mlx_ptr);
int		close_window(t_mlx *mlx_ptr);
void	init_hooks(t_mlx *mlx_struct);


#endif