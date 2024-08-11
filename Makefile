NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./mlx/
UTILS := utils/init.c
HEADERS	:= -I ./inc -I $(LIBMLX)/include ./parse/parse/cub.h

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L "/Users/mel-houd/.brew/opt/glfw/lib" -pthread -lm

SRCS = raycasting/raycasting.c ./parse/parse/parse.c parse/p_entry.c\
	   ./parse/parse/utils.c main.c parse/garbage_collector/garb_col.c \
		parse/get_next_line/get_next_line.c parse/get_next_line/get_next_line_utils.c \
		parse/parse/linked_list.c parse/parse/parse2.c parse/parse/utils2.c parse/parse/parse3.c \
		parse/parse/utils4.c parse/parse/parse4.c parse/parse/utils3.c parse/parse/parse5.c \
		raycasting/texture_handle.c ./utils/init.c drawing/tool_kit.c raycasting/cast.c physics/movement_and_collision.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re libmlx
