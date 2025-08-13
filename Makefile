NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
INCLUDES = -I./includes -I./libft -I./MLX42/include
LDFLAGS = -L./libft -lft -L./MLX42/build -lmlx42 -ldl -lglfw -pthread -lm

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/parser.c \
      $(SRCDIR)/parser_utils.c \
      $(SRCDIR)/parser_utils2.c \
      $(SRCDIR)/draw.c \
      $(SRCDIR)/draw_utils.c \
      $(SRCDIR)/draw_helpers.c \
      $(SRCDIR)/camera.c \
      $(SRCDIR)/projection.c \
      $(SRCDIR)/transform.c \
      $(SRCDIR)/color.c \
      $(SRCDIR)/events.c \
      $(SRCDIR)/mouse.c \
      $(SRCDIR)/keyboard.c \
      $(SRCDIR)/ui.c \
      $(SRCDIR)/ui_overlay.c \
      $(SRCDIR)/ui_info.c \
      $(SRCDIR)/ui_info_helpers.c \
      $(SRCDIR)/ui_text.c \
      $(SRCDIR)/ui_sections.c \
      $(SRCDIR)/ui_sections_helpers.c \
      $(SRCDIR)/utils.c \
      $(SRCDIR)/error.c \
      $(SRCDIR)/init.c \
      $(SRCDIR)/cleanup.c

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = ./MLX42
MLX42 = $(MLX42_DIR)/build/libmlx42.a

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@printf "Compiling %s\n" $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@printf "Building libft...\n"
	@make -C $(LIBFT_DIR)

$(MLX42):
	@printf "Building MLX42...\n"
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(LIBFT) $(MLX42) $(OBJ)
	@printf "Linking %s\n" $(NAME)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@printf "\033[32m✓ %s built successfully\033[0m\n" $(NAME)

clean:
	@printf "Cleaning object files...\n"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@printf "Cleaning executables...\n"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX42_DIR)/build

re: fclean all

norm:
	@norminette $(SRCDIR) $(INCDIR) $(LIBFT_DIR)

.PHONY: all clean fclean re norm