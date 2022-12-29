CC = cc
RM = rm -rf
XFLAGS = -Wall -Wextra -Werror  -Imlx -fsanitize=address -g

SRC =  	main.c cub3d_outils.c draw_minimap.c init.c move_player.c dda.c check_walls.c \
		parsing/check_error.c \
		parsing/libft/ft_strlen.c \
		parsing/libft/ft_memmove.c \
		parsing/libft/ft_memcpy.c \
		parsing/get_next_line/get_next_line.c \
		parsing/get_next_line/get_next_utils.c \
		parsing/utils.c \
		ray_tools.c

OBJ = ${SRC:.c=.o}
NAME = cub
LIB  = header.h parsing/cub3d.h

all : ${NAME}

${NAME} : ${OBJ} ${LIB}
		${CC} -g ${XFLAGS} ${OBJ}  -lmlx -framework OpenGL -framework AppKit -o ${NAME}
		
%.o : %.c ${LIB}
	${CC} -g ${XFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM}  ${NAME}

re: fclean all

.PHONY: clean fclean re all