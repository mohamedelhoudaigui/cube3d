
#ifndef DEFINES_H
#define DEFINES_H

#include "struct.h"
#include "../mlx/include/MLX42/MLX42.h"

void update_player_position(t_info *info, double move_speed,
                            double strafe_speed);
void check_collision(t_info *info, t_point move, t_point strafe, t_point new);
void handle_player_movement(t_info *info, mlx_key_data_t key);
int get_offset(mlx_image_t *image, t_point pixel) ;

#endif
