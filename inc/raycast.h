#ifndef RAYCAST_H
#define RAYCAST_H

#include <math.h>
#include "../mlx/include/MLX42/MLX42.h"
#include "struct.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>

void		player_move_d(t_player *);
void		player_move_a(t_player *);
void		player_move_s(t_player *);
void		player_move_w(t_player *);
void		renderer(t_info *info);
t_map		load_map_data(t_map *map);
void    	clear_window(mlx_t *mlx);
void    	raycaster(t_info *);
void    	test_cast(t_info *info);



#endif
