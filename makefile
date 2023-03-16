NAME	= Cub3D

CC		= gcc

Make	= make

OS	= $(shell uname)

ifeq ($(DB),1)
    CFLAGS	= -O3 -g3 -Wall -Wextra -Werror - g#debuger flaf
	LIBS	= -L libft/ -lft ${MLX_LNK} -lm
	MKBONUS	= DB=1 -C srcs/bonus
else
	CFLAGS	= -O2 #-Wall -Wextra -Werror -fsanitize=address
	LIBS	= -L libft/ -lft ${MLX_LNK} -lm
	MKBONUS	= -C srcs/bonus
endif

INC		= -I includes/ -I libft/includes/ -I $(MLX_DIR) # -I srcs/get_next_line/

OBJS	= ${SRCS:.c=.o}

SRCS	=	srcs/main.c \
			srcs/key_hook.c \
			srcs/pixel_put.c \
			srcs/init.c \
			srcs/draw.c \
			srcs/move.c \
			srcs/calculations.c \
			srcs/parser_floor_ceiling.c \
			srcs/parser_init.c \
			srcs/parser_map.c \
			srcs/parser_textures.c \



ifeq ($(OS), Linux)
	MLX_DIR	= minilibx-linux
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
#	SRCS	+=	srcs/events/mouse_bonus.c \
				srcs/parser/resolution_parser.c
else
	MLX_DIR	= minilibx-opengl
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
#	SRCS	+=	srcs/events/mouse_mac_bonus.c \
				srcs/parser/resolution_mac_parser.c
endif

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INC}

${NAME}: ${OBJS} ft mlx
		@echo "\033[35m-= Making Cub3D... =-"
		${CC} ${CFLAGS} ${INC} ${OBJS} ${LIBS} -o ${NAME}
		@echo "\033[32m   ______      __   _____ ____  "
		@echo "\033[32m  / ____/_  __/ /_ |__  // __ \ "
		@echo "\033[32m / /   / / / / __ \ /_ </ / / / "
		@echo "\033[32m/ /___/ /_/ / /_/ /__/ / /_/ /  "
		@echo "\033[32m\____/\__,_/_.___/____/_____/   usage: ./Cub3D <map.cub> [--save]"

mlx:
	@echo "\033[34m-= Making mlx... =-"
	@make -C $(MLX_DIR)
	@echo "\033[34m-= mlx Done ! =-"

ft:
	@echo "\033[33m-= Making Libft... =-"
	@make -C libft
	@make bonus -C libft
	@echo "\033[33m-= Libft Done ! =-"

bonus:
	rm -f ${OBJS} ${NAME}
	@make ${MKBONUS}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	@echo "\033[33m-= Cleaning Libft... =-"
	@make fclean -C libft
	@echo "\033[34m-= Cleaning mlx... =-"
	@make clean -C $(MLX_DIR)
	@echo "\033[35m-= Cleaning Cub3D... =-"
	rm -f ${NAME}
	@echo "Done.\033[0;0m"

re: fclean all

.PHONY: all clean fclean re bonus mlx ft
