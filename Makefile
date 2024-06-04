SRCS = ./parse/parse.c ./parse/utils.c ./raycasting/raycaster.c \
		./raycasting/mlx_functions.c ./raycasting/map_draw.c \
		./raycasting/key_hooks.c ./raycasting/utils_r.c ./raycasting/color.c \
		./raycasting/draw_funcs.c

OBJS = $(SRCS:.c=.o)

CC = cc

OFLAGS =  -Wall -Wextra -Werror -g -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror -c

RM = rm -f

NAME = cub3D

HEADERS = cube.h

LIB = make -C ./include

LIB_PATH = ./include

LIB_ARC = ./include/libft.a

all : lib $(NAME)

lib :
	$(LIB)

$(NAME) : $(OBJS)
	$(CC) $(OFLAGS) -o $(NAME) $(OBJS) $(LIB_ARC)

%.o: %.c $(HEADERS)
	$(CC) $(CFlAGS) -c $< -o $@

clean:
	make -C ./include clean
	$(RM) $(OBJS)

fclean : clean
	make -C ./include fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean lib
