# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:13:57 by dguy-caz          #+#    #+#              #
#    Updated: 2018/03/12 15:59:34 by notraore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	rt
LIBFT 		= 	libft/libft.a
PRINTF 		= 	ft_printf/libftprintf.a
MLX			= 	minilibx_macos/libmlx.a

SRCS		= 	srcs/main.c \
				srcs/cast_ray.c \
				srcs/basic_intersection.c \
				srcs/check_intersection.c \
				srcs/intersection_tools.c \
				srcs/solution.c \
				srcs/errors.c \
				srcs/errors_2.c \
				srcs/errors_3.c \
				srcs/load_scenes.c \
				srcs/load_obj.c \
				srcs/parsing_obj.c \
				srcs/ft_remove_if.c \
				srcs/wrap_obj.c \
				srcs/paraboloid.c \
				srcs/save/save_image.c \
				srcs/save/save_scene.c \
				srcs/save/create_save.c \
				srcs/save/put_save.c \
				srcs/save/utils_save.c \
				srcs/save/save_loop.c \
				srcs/save/put_material.c \
				srcs/interactions/user_interactions.c \
				srcs/interactions/mouse.c \
				srcs/interactions/mouse_tools.c \
				srcs/interactions/inputs.c \
				srcs/interactions/inputs4.c \
				srcs/interactions/interface.c \
				srcs/interactions/copy_delete.c \
				srcs/render/anti_aliasing.c \
				srcs/render/pixelization.c \
				srcs/render/filter.c \
				srcs/render/ray_tracer.c \
				srcs/render/multithread.c \
				srcs/matrix/camera.c \
				srcs/matrix/matrix_rotation.c \
				srcs/matrix/matrix_translation.c \
				srcs/matrix/matrix_tools.c \
				srcs/parsing/parsing.c \
				srcs/parsing/parse_material.c \
				srcs/parsing/parse_material2.c \
				srcs/parsing/parse_indice.c \
				srcs/parsing/choose_material.c \
				srcs/parsing/choose_material2.c \
				srcs/parsing/choose_material3.c \
				srcs/parsing/choose_material4.c \
				srcs/parsing/choose_material5.c \
				srcs/parsing/choose_material6.c \
				srcs/parsing/parsing_tools.c \
				srcs/parsing/get_parsing.c \
				srcs/parsing/get_object.c \
				srcs/parsing/create_object.c \
				srcs/parsing/create_object2.c \
				srcs/parsing/object_attribut.c \
				srcs/parsing/create_cap.c \
				srcs/parsing/create_cube.c \
				srcs/parsing/create_pyramide.c \
				srcs/parsing/create_glass.c \
				srcs/parsing/create_light.c \
				srcs/parsing/create_area_light.c \
				srcs/parsing/triangle.c \
				srcs/parsing/quad.c \
				srcs/color/colors.c \
				srcs/color/bump.c \
				srcs/color/colors_op1.c \
				srcs/color/colors_op2.c \
				srcs/color/recurse_color.c \
				srcs/color/area_light.c \
				srcs/color/perlin_noise.c \
				srcs/color/texture.c \
				srcs/color/texture_2.c \
				srcs/vector/vectors_op1.c \
				srcs/vector/vectors_op2.c \
				srcs/vector/vectors_op3.c \

OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))

CC			= 	gcc 
CFLAGS		= 	-Wall -Wextra -Werror -g -O2
INC			= 	-I./includes/
LIBFTLINK	= 	-L./libft -lft
MLXLINK		= 	-L./minilibx_macos -framework OpenGL -framework AppKit -Iminilibx_macos

CG = \033[92m
CY = \033[93m
CE = \033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
			@ make -C ./libft all
			@ make -C ./ft_printf all
			@ make -C ./minilibx_macos all
			@ $(CC) $(CFLAGS) $(LIBFT) $(PRINTF) $(MLX) $(LIBFTLINK) $(MLXLINK) -o $@ $^
			@ echo "\n\033[92m---> RT program created ✓\033[0m";

objs/%.o:	srcs/%.c
			@ mkdir -p objs
			@ mkdir -p objs/parsing
			@ mkdir -p objs/color
			@ mkdir -p objs/vector
			@ mkdir -p objs/matrix
			@ mkdir -p objs/render
			@ mkdir -p objs/interactions
			@ mkdir -p objs/save
		 	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@
		 	@ echo "\033[K$(CY)[RT] :$(CE) $(CG)Compiling $<$(CE) \033[1A";


clean:		
			@ make -C libft/ clean
			@ make -C ./ft_printf clean
			@ make -C ./minilibx_macos clean
			@ /bin/rm -rf objs/
			@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean:		clean
			@ /bin/rm -f $(NAME)
			@ make -C libft/ fclean
			@ make -C ./ft_printf fclean
			@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";
re : fclean all

.PHONY: all, clean, fclean, re
.SILENT:
