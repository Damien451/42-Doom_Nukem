# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 14:47:48 by roduquen          #+#    #+#              #
#    Updated: 2019/10/25 14:48:29 by roduquen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOGIN = `whoami`

# **************************************************************************** #
#                                   BINARIES                                   #
# **************************************************************************** #

NAME = doom-nukem

# **************************************************************************** #
#                                  COMPILATION                                 #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra #-Werror

FSAN = #-fsanitize=address
DEBUG = #-g3
OPTI = -O2 -Ofast

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

SRCDIR = srcs
OBJDIR = .objs
INCDIR = includes
LIBDIR = libft
BREWDIR = /Users/$(LOGIN)/.brew

ANIM = animations
MATHS = maths
STATES = states
SHAPES = shapes
CAMERA = camera
RT = raytracing

S_ANIMDIR = ./$(SRCDIR)/$(ANIM)
S_MATHDIR = ./$(SRCDIR)/$(MATHS)
S_STATDIR = ./$(SRCDIR)/$(STATES)

O_ANIMDIR = ./$(OBJDIR)/$(ANIM)
O_MATHDIR = ./$(OBJDIR)/$(MATHS)
O_STATDIR = ./$(OBJDIR)/$(STATES)

# **************************************************************************** #
#                                 INCLUDES                                     #
# **************************************************************************** #

LIBSDL = $(BREWDIR)/lib/ -lSDL2-2.0.0 -lSDL2_ttf-2.0.0 -lSDL2_image-2.0.0 `sdl2-config --cflags --libs`
INCSDL = $(BREWDIR)/include/SDL2
LIBFT = $(LIBDIR) -lft

# **************************************************************************** #
#                                  SOURCES                                     #
# **************************************************************************** #

SRCS =		$(ANIM)/anim_main_menu.c				\
			$(ANIM)/create_flame.c					\
			$(CAMERA)/camera.c						\
			$(CAMERA)/camera_commands.c				\
			$(STATES)/state_get_input.c				\
			$(STATES)/state_main_menu.c				\
			$(STATES)/state_scoreboard.c			\
			$(STATES)/state_settings_menu.c			\
			$(STATES)/state_start.c					\
			$(MATHS)/quaternion.c					\
			$(MATHS)/quaternion_2.c					\
			$(MATHS)/vec3l_maths.c					\
			$(MATHS)/vec3l_maths_2.c				\
			$(MATHS)/vec3d_maths.c					\
			$(MATHS)/vec3d_maths_2.c				\
			$(MATHS)/create_octree.c				\
			$(RT)/raytracing.c						\
			$(RT)/ray_intersect.c					\
			$(SHAPES)/draw_circle.c					\
			$(SHAPES)/draw_rectangle.c				\
			$(STATES)/state_editor.c				\
			$(STATES)/state_game.c					\
			$(STATES)/state_main_menu.c				\
			$(STATES)/state_play_menu.c				\
			$(STATES)/state_settings_menu.c			\
			add_points.c							\
			doom.c									\
			frame_calculator.c						\
			get_default_inputs.c					\
			init_program.c							\
			leave_program.c							\
			parse_input_file.c						\
			program.c								\
			put_buttons_names.c						\
			put_buttons_on_img.c					\
			put_string_on_renderer.c				\
			utils.c

# **************************************************************************** #
#                                   UTILS                                      #
# **************************************************************************** #

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

DPDCS = $(OBJS:.o:.d)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -L $(LIBFT) -L $(LIBSDL) -o $@ $^
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

-include $(DPDCS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -I $(INCDIR) -I $(INCSDL) -I $(LIBDIR) -MMD -o $@ -c $<
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(OBJDIR) :
	@mkdir -p $(OBJDIR) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(ANIM) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(MATHS) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(STATES) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(SHAPES) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(CAMERA) 2> /dev/null || true
	@mkdir -p $(OBJDIR)/$(RT) 2> /dev/null || true

clean :
	@rm -rf $(OBJDIR)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"
	@make -C libft fclean

cm : clean all

re : fclean all

.PHONY : all clean fclean cm re
