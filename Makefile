# Define color codes
ORANGE = \033[38;5;214m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

# Program file name
CUB3D = cub3D
NAME = $(CUB3D)

# Directories
SRCDIR = src/
OBJDIR = objs/
MAPDIR = maps/

# sub directory
INITDIR = $(SRCDIR)initialize/
RAYCASTDIR = $(SRCDIR)raycast/
PLAYERDIR = $(SRCDIR)player/
UTILSDIR = $(SRCDIR)utils/
PARDIR = $(SRCDIR)parsing/
VALDIR = $(SRCDIR)validate/

# Source files
SRC_FILES = main.c \
            $(INITDIR)init.c \
            $(INITDIR)init_utils.c \
            $(PLAYERDIR)player.c \
            $(PLAYERDIR)rotate.c \
			$(PLAYERDIR)mouse.c \
			$(PLAYERDIR)torch.c \
			$(PLAYERDIR)movement.c \
            $(RAYCASTDIR)raycast.c \
            $(RAYCASTDIR)raycast_utils.c \
			$(RAYCASTDIR)texture.c \
			$(UTILSDIR)utils.c \
			$(VALDIR)valid_file.c\
			$(VALDIR)valid_file_utils.c\
			$(VALDIR)valid_file_mem.c\
			$(VALDIR)valid_texture.c\
			$(PARDIR)main_map_check.c\
			$(PARDIR)map_check_utils.c\
			$(PARDIR)map_check.c\
			$(PARDIR)map_utils.c\
			$(PARDIR)map_wall.c\

SRCS = $(addprefix $(SRCDIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))

# Compiler and compilation flags
CC = gcc
#CFLAGS = -Werror -Wextra -Wall -g3 #-fsanitize=address

# Minilibx
MLX_PATH = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# Include directories
INCLUDES = -I includes/ -I $(MLX_PATH) -I $(LIBFT_PATH)  -I $(INITDIR) -I $(PLAYERDIR) -I $(RAYCASTDIR) -I $(MAPDIR) -I $(UTILSDIR) -I $(PARDIR) -I $(VALDIR)

# Linker flags
LDFLAGS = -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) -lft -lm -lbsd -lX11 -lXext

# Build the program
all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo -e "\n\n\n$(YELLOW) -- DONE COMPILING CUB3D, LET'S BEGIN THE GAME NOW ! --$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)initialize
	@mkdir -p $(OBJDIR)raycast
	@mkdir -p $(OBJDIR)player
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(INITDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(PLAYERDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@
	
$(OBJDIR)%.o: $(UTILSDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(RAYCASTDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(PARDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(VALDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(MLX_PATH) clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)

re: fclean all

# norm :
# 	norminette ./includes
# 	norminette ./libft
# 	norminette ./src

valgrind :
	valgrind --leak-check=full ./cub3D

.PHONY: all re clean fclean