
#include "../inc/draw.h"
#include "../inc/macros.h"
#include "../inc/struct.h"
#include <math.h>


//void draw_line2(t_vector vector, t_info *info)
//{
//  int x1 = vector.start.x;
//  int y1 = vector.start.y;
//  int x2 = vector.end.x;
//  int y2 = vector.end.y;
//  int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
//  int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
//  int err = dx + dy, e2;
//  mlx_image_t *image = info->img;
//  t_point point;

//  point.x = 0;
//  point.y = 0;

//  while (1)
//  {
//    point.x = x1;
//    point.y = y1;
//    put_pixel(image, point, COLOR);
//    if (x1 == x2 && y1 == y2)
//      break;
//    if (x1 >= SCREEN_WIDTH || x2 >= SCREEN_WIDTH)
//      break;
//    if (y1 >= SCREEN_HEIGHT || y2 >= SCREEN_HEIGHT)
//      break;
//    e2 = 2 * err;
//    if (e2 >= dy) {
//      err += dy;
//      x1 += sx;
//    }
//    if (e2 <= dx) {
//      err += dx;
//      y1 += sy;
//    }
//  }
//}


bool put_pixel(mlx_image_t *data, int x, int y, int color)
{
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
      mlx_put_pixel(data, x, y, color);
  }
  else {
      printf("[DEBUG] : Out of bounds at {%d, %d}\n", x, y);
      return false;
  }
  return true;
}

t_point add_vector(t_point start, t_point end)
{
    t_point vector;

    vector.x = start.x + end.x;
    vector.y = start.y + end.y;
    return (vector);

}
//return = (v1.x - v2.x).(v1.y - v2.y)
t_point subtract_vector(t_point start, t_point end)
{
    // returns the vecter pointing at start pos from end pos
    t_point vector;

    vector.x = start.x - end.x;
    vector.y = start.y - end.y;
    return (vector);
}

int vector_len(t_point vector)
{
    int len;
    int x  = vector.x;
    int y  = vector.y;

    len = sqrt((x * x) + (y * y));

    return (len);
}

int vector_len_sqrt(t_point vector)
{
    int len;
    int x  = vector.x;
    int y  = vector.y;

    len = (x * x) + (y * y);

    return (len);
}

void clear_window(mlx_t *mlx) { mlx_close_window(mlx); }

// left sided draw
//void draw_line(mlx_t *mlx, int len, t_point starting_position, bool mode) {
//  int i = 0;
//  int x = starting_position.x;
//  int y = starting_position.y;

//  if (mode == true) {
//    while (i < len) {
//      put_pixel(img, x, y, COLOR);
//      x++;
//      i++;
//    }
//  } else {
//    while (i < len) {
//      put_pixel(img, x, y, COLOR);
//      y++;
//      i++;
//    }
//  }
//}


//void draw_slant(t_info *info, t_point position, t_point target) {
//  int diff_x = target.x - position.x + 1;
//  int diff_y = target.y - position.y + 1;
//  float ratio = diff_x / diff_y;

//  printf("diffx == %d\n", diff_x);
//  printf("diffy == %d\n", diff_y);
//  const float remainder = ratio - (int)ratio;
//  printf("remainder == %f\n", remainder);

//  (void)position;
//  while (diff_x < 100) {
//    mlx_put_pixel(info->mlx->mlx, info->mlx->mlx_win, diff_x, diff_y, COLOR);
//    diff_x++;
//    diff_y++;
//  }
//}


void circle_octants(t_info * info, int x, int y)
{
  // Draw points in all eight octants
  put_pixel(info->img, info->player->vector.start.x + x, info->player->vector.start.y + y,
              COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x + x, info->player->vector.start.y - y,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x - x, info->player->vector.start.y - y,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x - x, info->player->vector.start.y + y,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x + y, info->player->vector.start.y + x,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x - y, info->player->vector.start.y + x,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x - y, info->player->vector.start.y - x,
                COLOR); // Octant 1
  put_pixel(info->img, info->player->vector.start.x + y, info->player->vector.start.y - x,
                COLOR); // Octant 1
}

void drawcircle(t_info *info)
{
  int x = 0;
  int y = HIT_BOX;
  int d = 3 - 2 * HIT_BOX;

  // Draw the initial points on the circle
  circle_octants(info, x, y);

  // Loop to draw the circle using Bresenham's algorithm
  while (y >= x) {
    x++;
    // Update the decision parameter based on its current value
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    // Draw the points for the current (x, y)
    circle_octants(info, x, y);
  }
}
