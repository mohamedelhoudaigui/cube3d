
#ifndef DRAW_H
#define DRAW_H

#include "struct.h"
#include "../mlx/include/MLX42/MLX42.h"
#include <stdio.h>


//###########################################################################
// Drawing functions

void clear_window(mlx_t *mlx);
void draw_line(mlx_t *mlx, int len, t_point starting_position, bool mode);
void draw_slant(t_info *info, t_point position, t_point target);
void draw_tile(mlx_t *mlx, int len, t_point starting_position);
void draw_wall_ver(mlx_t *mlx, int len, int count, t_point starting_position);
void draw_wall_hor(mlx_t *mlx, int len, int count, t_point starting_position);
void draw_grid(mlx_t *mlx, int len, int count, t_point starting_position);
void circle_octants(t_info * info, int x, int y);
void drawcircle(t_info *info);
void draw_anyline(t_map *, t_point , t_point);
void    test(t_map *);
bool    put_pixel(mlx_image_t *img, int x, int y, int color);


void render_player(t_info *info) ;

//##########################################################################
// Vector arithmetic


int vector_len(t_point vector);
t_point subtract_vector(t_point start, t_point end);
t_point add_vector(t_point start, t_point end);



// textures:
mlx_texture_t	*get_side_tex(char wall_side, t_data *data);
unsigned int	get_tex_pixel_color(t_point *point, t_info *info);

#endif
