# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 12:43:57 by arvardan          #+#    #+#              #
#    Updated: 2026/04/25 20:31:37 by arvardan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

ifeq ($(DEBUG),debug)
CFLAGS += -g3
endif

ifeq ($(DEBUG),full)
CFLAGS += -g3 -fsanitize=address,undefined
endif

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX_DIR		= minilibx-macos
	MLX			= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	INCLUDES	= -Iincludes -Ilibft -I$(MLX_DIR)
else
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_Linux.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm
	INCLUDES	= -Iincludes -Ilibft -I$(MLX_DIR)
endif

SRC_FOLDER	= srcs
OBJ_FOLDER	= objs

SRC =	$(SRC_FOLDER)/main.c \
		$(SRC_FOLDER)/init.c \
		$(SRC_FOLDER)/utils/color.c \
		$(SRC_FOLDER)/utils/free.c \
		$(SRC_FOLDER)/utils/handle_whitespace.c \
		$(SRC_FOLDER)/utils/append.c \
		$(SRC_FOLDER)/utils/utils.c \
		$(SRC_FOLDER)/utils/fri.c \
		$(SRC_FOLDER)/parser/parse.c \
		$(SRC_FOLDER)/parser/parse_helper1.c \
		$(SRC_FOLDER)/parser/parse_helper2.c \
		$(SRC_FOLDER)/parser/parse_identifiers.c \
		$(SRC_FOLDER)/parser/parse_optional.c \
		$(SRC_FOLDER)/parser/parse_plane.c \
		$(SRC_FOLDER)/parser/parse_sphere.c \
		$(SRC_FOLDER)/parser/parse_cone.c \
		$(SRC_FOLDER)/parser/parse_cylinder.c \
		$(SRC_FOLDER)/parser/identify.c \
		$(SRC_FOLDER)/parser/parse_utils.c \
		$(SRC_FOLDER)/parser/check.c \
		$(SRC_FOLDER)/math/vec1.c \
		$(SRC_FOLDER)/math/vec2.c \
		$(SRC_FOLDER)/math/math.c \
		$(SRC_FOLDER)/renderer/intersections/intersect_sphere.c \
		$(SRC_FOLDER)/renderer/intersections/intersect_plane.c \
		$(SRC_FOLDER)/renderer/intersections/intersect_cylinder.c \
		$(SRC_FOLDER)/renderer/intersections/intersect_cylinder_helper.c \
		$(SRC_FOLDER)/renderer/intersections/intersect_cone.c \
		$(SRC_FOLDER)/renderer/intersections/intersection_utils.c \
		$(SRC_FOLDER)/renderer/intersections/obj_hit_normal.c \
		$(SRC_FOLDER)/renderer/intersections/const_vals.c \
		$(SRC_FOLDER)/renderer/intersections/helper.c \
		$(SRC_FOLDER)/renderer/camera.c \
		$(SRC_FOLDER)/renderer/lighting/diffuse_ambient.c \
		$(SRC_FOLDER)/renderer/lighting/shadow.c \
		$(SRC_FOLDER)/renderer/lighting/specular.c \
		$(SRC_FOLDER)/renderer/lighting/reflection.c \
		$(SRC_FOLDER)/renderer/render.c \
		$(SRC_FOLDER)/events/events.c \
		$(SRC_FOLDER)/events/key_wasd.c \
		$(SRC_FOLDER)/events/key_handle.c \
		$(SRC_FOLDER)/events/select_obj_light.c \
		$(SRC_FOLDER)/events/helper_func.c \
		$(SRC_FOLDER)/events/rotate.c \
		$(SRC_FOLDER)/events/resize_object.c \
		$(SRC_FOLDER)/patterns/checkerboard.c \
		$(SRC_FOLDER)/texture/load.c \
		$(SRC_FOLDER)/texture/uv_mapping.c \
		$(SRC_FOLDER)/texture/skybox.c \
		$(SRC_FOLDER)/texture/texture_utils.c

OBJS	= $(SRC:$(SRC_FOLDER)/%.c=$(OBJ_FOLDER)/%.o)
LIBFT	= libft/libft.a
NAME	= miniRT

R	= \033[0;31m
Y	= \033[1;33m
RS	= \033[0m

HEADERS = includes/minirt.h includes/defines.h includes/structs.h

all: $(LIBFT) $(MLX) $(NAME)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@printf "$(R)⚙️  building libft...$(RS)\n"
	@$(MAKE) -C libft --silent > /dev/null 2>&1

$(MLX):
	@printf "$(R)⚙️  building minilibx...$(RS)\n"
	@$(MAKE) -C $(MLX_DIR) --silent > /dev/null 2>&1

$(NAME): $(OBJS)
	@printf "$(Y)🔧 linking objects...$(RS)\n"
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft $(MLX_FLAGS) -o $(NAME)
	@printf "$(R)✅ build complete: ./$(NAME)$(RS)\n"
	@sleep 0.07
	@printf "\033[38;5;51m███╗░░░███╗██╗███╗░░██╗██╗██████╗░████████╗\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;45m████╗░████║██║████╗░██║██║██╔══██╗╚══██╔══╝\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;39m██╔████╔██║██║██╔██╗██║██║██████╔╝░░░██║░░░\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;33m██║╚██╔╝██║██║██║╚████║██║██╔══██╗░░░██║░░░\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;27m██║░╚═╝░██║██║██║░╚███║██║██║░░██║░░░██║░░░\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;21m╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═╝░░╚═╝░░░╚═╝░░░\033[0m\n"
	@sleep 0.07
	@printf "\033[38;5;33m    👽 MADE BY: arvardan and ipogodae👽\033[0m\n"

bonus: all

clean:
	@$(MAKE) -C libft clean --silent > /dev/null 2>&1
	@$(MAKE) -C $(MLX_DIR) clean --silent > /dev/null 2>&1
	@rm -rf $(OBJ_FOLDER)
	@printf "$(R)🧹 objects cleaned!$(RS)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(R)🔥 $(NAME) removed!$(RS)\n"

re: fclean all

.PHONY: all clean fclean re bonus