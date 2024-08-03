SRCS = parse.c utils.c main.c ./garbage_collector/garb_col.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		linked_list.c parse2.c utils2.c parse3.c utils3.c utils4.c parse4.c


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

NAME = cub3D

HEADERS = cube.h ./garbage_collector/garbage.h ./get_next_line/get_next_line.h


all : $(NAME)


$(NAME) : $(OBJS)
	$(CC) $(OFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFlAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean
