/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:52:41 by mel-houd          #+#    #+#             */
/*   Updated: 2024/06/05 02:31:07 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// angles :
// 45 - down
// -45 - right
// 135 - left
// -135 - up


// keys :
// right 124
// down 125
// left 123
// up 126


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

# define X 1000
# define Y 1000
# define PI 3.14159265
# define TITLE "cub3D"
# define ANGEL_OFFSET 10

typedef	struct	s_morphed
{
	char	*NO_tex;
	char	*SO_tex;
	char	*WE_tex;
	char	*EA_tex;
	int		*f_num;
	int		*c_num;
	char	**map;
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct s_mlx
{
	void		*mlx_srv;
	void		*mlx_win;
	t_data		*img;
	t_data		*rays_img;
	t_morphed	*map;
	int			angle;
	t_list		*rays_inter;
}				t_mlx;

typedef struct s_vector
{
	int		x_start;
	int		y_start;
	int		x_finish;
	int		y_finish;
	char	map_char;
}				t_vector;

//----------parsing headers :

t_morphed	*parse(int ac, char **av);
t_init_map	*null_init(void);
t_morphed	*null_init2(t_init_map *data);
char		*ft_trim_end(char *str, char *set);
bool    	check_equal(char *s1, char *s2);
void		assign_lines(t_list *head, t_init_map **init_data_p);
t_list		*from_file(char *file_name, t_list **head);
bool    	check_chars(char *s, char *set);
int			biggest_line(t_list *map);
char   	 	*morph_line(char *str, int len, char append);
bool		check_borders(char **map);
bool		check_map_elements(char **map);
bool		check_line(char *s, int mode);
char		**alter_map(t_init_map *init_data);
void		assign_color(t_init_map *init_data, t_morphed *refined_map);
int			*extract_color(char *color);
void		print_morphed(t_morphed *data);

//------------raycasting headers :
t_mlx	*init_mlx(t_morphed *full_map);
int		key_hook(int keycode, t_mlx *mlx_struct);
int		close_window(t_mlx *mlx_ptr);
void	init_hooks(t_mlx *mlx_struct);
int		get_color(int r, int g, int b);
int 	get_char_color(char map_char);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
char	get_pixel(t_data *data, int x, int y);
void    draw_map(t_mlx *mlx_struct);
void    draw_square(t_vector *map_element, t_mlx *mlx_struct);
void    draw_map_line(t_vector *map_element, t_mlx *mlx_struct, t_data *img);
int 	*get_player_pos(char **map);
void    move_up(t_mlx *mlx_struct);
void    move_down(t_mlx *mlx_struct);
void    move_left(t_mlx *mlx_struct);
void    move_right(t_mlx *mlx_struct);
void    draw_line(t_vector *line, t_mlx *mlx_struct);
void    draw_rays(t_mlx *mlx_struct);
void    draw_rays_img(t_mlx *mlx_struct);
void    put_img(t_mlx *mlx_struct, t_data *chosen_img);



#endif