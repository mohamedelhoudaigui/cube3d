
#include "inc/defines.h"
#include "inc/macros.h"
#include "inc/raycast.h"
#include "inc/struct.h"
#include "inc/utils.h"
#include <stdio.h>
#include <stdlib.h>

void free_arr(char **arr) {
  int i = 0;
  while (arr[i] != NULL) {
    free(arr[i]);
  }
}

void free_all(t_info *info) {

  void *mlx;

  mlx = info->mlx;

  mlx_terminate(mlx);
  exit(EXIT_FAILURE);
}






void key_hook(mlx_key_data_t key, t_info *info)
{
  if (key.key == ESC_KEY)
    free_all(info);
  else {
    handle_player_movement(info, key);
  }
}

void new_image(t_info *info) {
  info->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool game_init(t_info *info) {

  mlx_t *mlx;
  mlx = info->mlx;
  mlx_image_t *image;
  image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (image == NULL)
    return false;
  info->img = image;

  mlx_key_hook(mlx, (void *)key_hook, info);
  mlx_loop_hook(mlx, (void *)renderer, info);
  mlx_loop(mlx);
  return true;
}

t_info *vars_init(int ac, char **av) {

  t_data *data;
  t_info *info;

  data = parse_entry(ac, av);
  info = malloc(sizeof(t_info));
  info->data = data;
  info->mlx = data->ini;
  info->map = data->map;
  info->player = player_init();

  return (info);
}

int main(int ac, char **av) {
  game_init(vars_init(ac, av));
  return 1;
}
