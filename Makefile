# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srachdi <srachdi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 20:02:22 by srachdi           #+#    #+#              #
#    Updated: 2023/08/27 14:55:52 by srachdi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
NAME_BONUS = miniRT_Bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
MLX_FLAGS = -lmlx -framework openGL -framework appkit 
SRCS = manditory/main.c  manditory/light_utils.c manditory/vec2.c manditory/utils3.c manditory/utils4.c manditory/plane.c manditory/misc.c  manditory/atod.c manditory/light.c  manditory/camera.c  manditory/free_stuff.c  manditory/parse.c manditory/color.c  manditory/draw.c manditory/vec.c manditory/ray.c manditory/cylinder.c manditory/sphere.c manditory/intersections.c manditory/amb_cam_lght.c manditory/sp_pl_cy_cn.c manditory/utils.c manditory/utils2.c manditory/get_next_line/get_next_line_utils.c manditory/get_next_line/get_next_line.c
SRCS_BONUS = bonus/main_bonus.c  bonus/utils4_bonus.c bonus/light_utils_bonus.c bonus/vec2_bonus.c bonus/utils3_bonus.c bonus/plane_bonus.c bonus/cone_bonus.c bonus/uv_bonus.c bonus/misc_bonus.c bonus/texture_bonus.c bonus/atod_bonus.c bonus/light_bonus.c  bonus/camera_bonus.c  bonus/free_stuff_bonus.c bonus/patterns_bonus.c bonus/parse_bonus.c bonus/color_bonus.c  bonus/draw_bonus.c bonus/vec_bonus.c bonus/ray_bonus.c bonus/cylinder_bonus.c bonus/sphere_bonus.c bonus/intersections_bonus.c bonus/amb_cam_lght_bonus.c bonus/sp_pl_cy_cn_bonus.c bonus/utils_bonus.c bonus/utils2_bonus.c bonus/get_next_line/get_next_line_utils_bonus.c bonus/get_next_line/get_next_line_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INC = manditory/minirt.h
INC_BONUS = bonus/minirt_bonus.h

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
all : $(NAME)
	@echo "\033[1;36m ./miniRT [filename].rt\033[0m"
$(NAME) :  $(OBJS)
	@$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(MLX_FLAGS)

all : $(NAME)

bonus : $(NAME_BONUS)
	@echo "\033[1;35m ./miniRT_Bonus [filename].rt\033[0m"
$(NAME_BONUS) : $(OBJS_BONUS) $(INC_BONUS)
	@$(CC) $(CFLAGS)  -o $(NAME_BONUS) $(OBJS_BONUS) $(MLX_FLAGS)
clean :
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "\033[0;31m removed obj.\033[0m"
fclean : clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "\033[0;31m removed bin. \033[0m"
re : fclean all

.PHONY : all clean fclean re bonus