/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houd <mel-houd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:04:46 by mel-houd          #+#    #+#             */
/*   Updated: 2024/08/12 20:38:30 by mel-houd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "struct.h"
# include <mlx.h>
# include <math.h>

void			clear_window(t_mlx *mlx);
bool			put_pixel(t_img *img, t_point pixel, int color);
t_texture		*get_side_tex(char wall_side, t_data *data);
unsigned int	get_tex_pixel_color(int y2, t_info *info, t_point p);
void			initialize_ray_direction(t_ray_info *ri, t_point pos,
					double angle);
void			put_skye_color(t_info *info, int color);
void			put_floor_color(t_info *info, int color);
void			draw_wall_column(t_info *info, int x, t_point p,
					t_wall_info *wi);
void			calculate_wall_dimensions(t_wall_info *wi, t_info *info,
					double dist, double angle);
void			calculate_ray_length(t_ray_info *ri, t_point pos);
void			draw_wall_strip(t_info *info, int x, double dist, t_point p);
void			calculate_step(t_ray_info *ri, double *dist, t_info *info);
void			check_reset_player_angle(t_player *player);
double			raycast(t_point pos, double angle, t_vector *vector,
					t_info *info);
int				perform_dda(t_info *info, t_ray_info *ri, double *dist);
void			set_player_position(t_info *info, int i, int j);
void			set_player_angle(t_info *info, char direction);
void			process_map_tile(t_info *info, char **map, int i, int j);
void			set_player_spawn(t_info *info);

#endif
