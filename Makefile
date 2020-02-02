LOGIN		= `whoami`

# **************************************************************************** #
#                                   BINARIES                                   #
# **************************************************************************** #

NAME		= doom-nukem

# **************************************************************************** #
#                                  COMPILATION                                 #
# **************************************************************************** #

CC 			= clang
CFLAGS		= -Wall -Wextra #-Werror

FSAN		= #-fsanitize=address
DEBUG		= -g3
OPTI		= -Ofast

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

SRCDIR		= srcs
OBJDIR		= .objs
INCDIR		= includes
LIBDIR		= libft
BREWDIR		= /Users/$(LOGIN)/.brew

ANIM		= animations
CAMERA		= camera
EDITOR		= editor
MATHS		= maths
PROG		= program
RAST		= rasterization
RT			= raytracing
SHAPES		= shapes
SOUND		= sound
STATES		= states
UI			= ui

S_ANIMDIR	= ./$(SRCDIR)/$(ANIM)
S_MATHDIR	= ./$(SRCDIR)/$(MATHS)
S_STATDIR	= ./$(SRCDIR)/$(STATES)

O_ANIMDIR	= ./$(OBJDIR)/$(ANIM)
O_MATHDIR	= ./$(OBJDIR)/$(MATHS)
O_STATDIR	= ./$(OBJDIR)/$(STATES)

# **************************************************************************** #
#                                 INCLUDES                                     #
# **************************************************************************** #

LIBSDL		= $(BREWDIR)/lib/ -lSDL2-2.0.0 -lSDL2_mixer-2.0.0 -lSDL2_ttf-2.0.0 \
				-lSDL2_image-2.0.0 `sdl2-config --cflags --libs`
INCSDL		= $(BREWDIR)/include/SDL2
LIBFT		= $(LIBDIR) -lft

# **************************************************************************** #
#                                  SOURCES                                     #
# **************************************************************************** #

SRCS 		=		$(ANIM)/anim_main_menu.c				\
					$(ANIM)/display_scores.c				\
					$(CAMERA)/camera.c						\
					$(CAMERA)/camera_commands.c				\
					$(CAMERA)/clipping.c					\
					$(CAMERA)/clipping2.c					\
					$(CAMERA)/player_hitbox.c				\
					$(EDITOR)/check_map_validity.c			\
					$(EDITOR)/color_rectangle.c				\
					$(EDITOR)/deal_with_map_directory.c		\
					$(EDITOR)/editor_commands.c				\
					$(EDITOR)/editor_utils.c				\
					$(EDITOR)/editor_utils2.c				\
					$(EDITOR)/mouse_editor_commands.c		\
					$(EDITOR)/show_selected_params.c		\
					$(MATHS)/create_light_array.c			\
					$(MATHS)/create_octree.c				\
					$(MATHS)/create_octree_model.c			\
					$(MATHS)/matrix.c						\
					$(MATHS)/max_absolute_between_three.c	\
					$(MATHS)/octree_memory_management.c		\
					$(MATHS)/quaternion.c					\
					$(MATHS)/quaternion_2.c					\
					$(MATHS)/vec3l_maths.c					\
					$(MATHS)/vec3l_maths_2.c				\
					$(MATHS)/vec3d_maths.c					\
					$(MATHS)/vec3d_maths_2.c				\
					$(PROG)/doom.c							\
					$(PROG)/frame_calculator.c				\
					$(PROG)/init_func_pointers.c			\
					$(PROG)/init_map_colors.c				\
					$(PROG)/init_game.c						\
					$(PROG)/init_program.c					\
					$(PROG)/leave_program.c					\
					$(PROG)/leave_game.c					\
					$(PROG)/load_map.c						\
					$(PROG)/program.c						\
					$(PROG)/select_next_level.c				\
					$(PROG)/set_player_spawn.c				\
					$(RAST)/rasterization.c					\
					$(RT)/add_texture_neg.c					\
					$(RT)/add_texture_pos.c					\
					$(RT)/add_textures.c					\
					$(RT)/check_light_view_neg.c			\
					$(RT)/check_light_view_pos.c			\
					$(RT)/check_which_face_is_touched_neg.c	\
					$(RT)/check_which_face_is_touched_pos.c	\
					$(RT)/compute_lights.c					\
					$(RT)/cylinder.c						\
					$(RT)/launch_rays.c						\
					$(RT)/locate_in_octree.c				\
					$(RT)/plane.c							\
					$(RT)/print_octree.c					\
					$(RT)/ray_intersect.c					\
					$(RT)/ray_intersect_mini.c				\
					$(RT)/raytracing.c						\
					$(RT)/sphere.c							\
					$(RT)/sun_animation.c					\
					$(RT)/z_buffer.c						\
					$(SHAPES)/draw_circle.c					\
					$(SHAPES)/draw_rectangle.c				\
					$(SOUND)/get_default_sounds.c			\
					$(SOUND)/load_sounds.c					\
					$(SOUND)/mixer.c						\
					$(SOUND)/mixer2.c						\
					$(SOUND)/mouse_sound_commands.c			\
					$(STATES)/state_death.c					\
					$(STATES)/state_delete_map.c			\
					$(STATES)/state_editor.c				\
					$(STATES)/state_editor_menu.c			\
					$(STATES)/state_game.c					\
					$(STATES)/state_get_input.c				\
					$(STATES)/state_get_map_name.c			\
					$(STATES)/state_inputs_settings_menu.c	\
					$(STATES)/state_level_finished.c		\
					$(STATES)/state_main_menu.c				\
					$(STATES)/state_pause.c					\
					$(STATES)/state_play_edit_map.c			\
					$(STATES)/state_play_menu.c				\
					$(STATES)/state_sound_settings.c		\
					$(STATES)/state_start.c					\
					$(STATES)/state_scoreboard.c			\
					$(STATES)/state_settings_menu.c			\
					$(STATES)/state_sound_settings.c		\
					$(STATES)/state_test_mode.c				\
					$(UI)/convert_to_ppm.c					\
					$(UI)/create_buttons_inputs.c			\
					$(UI)/display_inventory.c				\
					$(UI)/get_default_inputs.c				\
					$(UI)/minimap.c							\
					$(UI)/parse_input_file.c				\
					$(UI)/parse_scores_file.c				\
					$(UI)/put_buttons_names.c				\
					$(UI)/put_buttons_on_img.c				\
					$(UI)/put_string_on_renderer.c			\
					$(UI)/put_string_with_shadow.c			\
					$(UI)/put_sound_bars.c					\
					$(UI)/put_health_bar.c					\
					add_points.c							\
					load_textures.c							\
					utils.c									\
					dictionnary_binary_tex.c


# **************************************************************************** #
#                                   UTILS                                      #
# **************************************************************************** #

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

DPDCS		= $(OBJS:.o=.d)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all				:
	@make -j 4 $(NAME)

$(NAME)			: $(OBJS)

	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -L $(LIBFT) -L $(LIBSDL) -o $@ $^
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

-include $(DPDCS)

$(OBJDIR)/%.o	: $(SRCDIR)/%.c | $(OBJDIR)

	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -I $(INCDIR) -I $(INCSDL) \
		-I $(LIBDIR) -MMD -o $@ -c $<
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(OBJDIR)		:

	@mkdir -p $@			2> /dev/null || true
	@mkdir -p $@/$(ANIM)	2> /dev/null || true
	@mkdir -p $@/$(CAMERA)	2> /dev/null || true
	@mkdir -p $@/$(EDITOR)	2> /dev/null || true
	@mkdir -p $@/$(MATHS)	2> /dev/null || true
	@mkdir -p $@/$(PROG)	2> /dev/null || true
	@mkdir -p $@/$(RAST)	2> /dev/null || true
	@mkdir -p $@/$(RT)		2> /dev/null || true
	@mkdir -p $@/$(SHAPES)	2> /dev/null || true
	@mkdir -p $@/$(SOUND)	2> /dev/null || true
	@mkdir -p $@/$(STATES)	2> /dev/null || true
	@mkdir -p $@/$(UI)		2> /dev/null || true

clean			:

	@rm -rf $(OBJDIR)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"
	@make -C libft clean

fclean			: clean

	@rm -rf $(NAME)
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"
	@make -C libft fclean

cm				: clean all

re				: fclean all

.PHONY			: all clean fclean cm re
