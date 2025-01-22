CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Imlx42/include/MLX42 -g
LIBS = -L$(MLX42_PATH) -lmlx42 -lglfw -ldl -pthread -lm
NAME = cub3d
MLX42_PATH = .
SRC_DIR = src
OBJ_DIR = obj


SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/keys_handling.c $(SRC_DIR)/clean.c $(SRC_DIR)/parsing.c $(SRC_DIR)/get_next_line.c $(SRC_DIR)/mapping.c $(SRC_DIR)/texture_parsing.c $(SRC_DIR)/parsing_map.c $(SRC_DIR)/parsing_utils.c $(SRC_DIR)/colors.c $(SRC_DIR)/utils.c  $(SRC_DIR)/utils3.c $(SRC_DIR)/utils2.c $(SRC_DIR)/get_next_line_utils $(SRC_DIR)/mlx.c $(SRC_DIR)/textures.c $(SRC_DIR)/keys.c  $(SRC_DIR)/render.c $(SRC_DIR)/mlx_utils.c $(SRC_DIR)/init_args.c $(SRC_DIR)/utils4.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/keys_handling.o $(OBJ_DIR)/clean.o $(OBJ_DIR)/parsing.o $(OBJ_DIR)/get_next_line.o $(OBJ_DIR)/mapping.o $(OBJ_DIR)/texture_parsing.o $(OBJ_DIR)/parsing_map.o $(OBJ_DIR)/parsing_utils.o $(OBJ_DIR)/colors.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/utils3.o $(OBJ_DIR)/utils2.o $(OBJ_DIR)/get_next_line_utils.o $(OBJ_DIR)/mlx.o	$(OBJ_DIR)/textures.o $(OBJ_DIR)/keys.o $(OBJ_DIR)/render.o $(OBJ_DIR)/mlx_utils.o $(OBJ_DIR)/init_args.o $(OBJ_DIR)/utils4.o
all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
