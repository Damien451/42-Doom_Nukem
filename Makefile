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
SDLDIR		= SDL2-2.0.12

ANIM		= animations
CAMERA		= camera
EDITOR		= editor
GAMEPLAY	= gameplay
MATHS		= maths
PROG		= program
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

LIBSDL		= $(SDLDIR)/lib/libSDL2.a SDL_text/ttf_build/lib/libSDL2_ttf.a SDL2_mixer-2.0.4/lib/libSDL2_mixer.a SDL_text/freetype_build/lib/libfreetype.a
INCSDL		= -I $(SDLDIR)/include -I SDL_text/ttf_build/include/SDL2 -I SDL2_mixer-2.0.4/include/SDL2

# **************************************************************************** #
#                                  SOURCES                                     #
# **************************************************************************** #

SRCS 		=		$(ANIM)/anim_main_menu.c				\
					$(ANIM)/anim_weapon.c					\
					$(ANIM)/display_arrows.c				\
					$(ANIM)/display_scores.c				\
					$(ANIM)/init_anim_state_start.c			\
					$(CAMERA)/camera.c						\
					$(CAMERA)/camera_commands.c				\
					$(CAMERA)/camera_keys.c					\
					$(CAMERA)/clipping.c					\
					$(CAMERA)/clipping2.c					\
					$(CAMERA)/player_hitbox.c				\
					$(EDITOR)/check_map_validity.c			\
					$(EDITOR)/color_rectangle.c				\
					$(EDITOR)/deal_with_map_directory.c		\
					$(EDITOR)/draw_block.c					\
					$(EDITOR)/editor_commands.c				\
					$(EDITOR)/editor_utils.c				\
					$(EDITOR)/editor_utils2.c				\
					$(EDITOR)/keydown_editor_commands.c		\
					$(EDITOR)/mouse_editor_commands.c		\
					$(EDITOR)/save_map_to_file.c			\
					$(EDITOR)/show_selected_params.c		\
					$(GAMEPLAY)/interaction.c				\
					$(GAMEPLAY)/init_enemies.c				\
					$(GAMEPLAY)/check_if_not_in_map.c		\
					$(GAMEPLAY)/check_pos_player.c			\
					$(GAMEPLAY)/get_item.c					\
					$(GAMEPLAY)/get_time_levels.c			\
					$(GAMEPLAY)/move_ennemies.c				\
					$(GAMEPLAY)/move_hitbox.c				\
					$(GAMEPLAY)/reload.c					\
					$(GAMEPLAY)/reset_game_values.c			\
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
					$(PROG)/add_new_highscore.c				\
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
					$(RT)/add_texture_neg.c					\
					$(RT)/add_texture_pos.c					\
					$(RT)/add_textures.c					\
					$(RT)/check_light_view_neg.c			\
					$(RT)/check_light_view_pos.c			\
					$(RT)/check_which_face_is_touched_neg.c	\
					$(RT)/check_which_face_is_touched_pos.c	\
					$(RT)/compute_lights.c					\
					$(RT)/cylinder.c						\
					$(RT)/event_loop.c						\
					$(RT)/launch_rays.c						\
					$(RT)/locate_in_octree.c				\
					$(RT)/plane.c							\
					$(RT)/print_octree.c					\
					$(RT)/ray_intersect.c					\
					$(RT)/ray_intersect_mini.c				\
					$(RT)/raytracing.c						\
					$(RT)/sphere.c							\
					$(RT)/sun_animation.c					\
					$(SHAPES)/draw_circle.c					\
					$(SHAPES)/draw_rectangle.c				\
					$(SOUND)/get_default_sounds.c			\
					$(SOUND)/load_sounds.c					\
					$(SOUND)/mixer.c						\
					$(SOUND)/mixer2.c						\
					$(SOUND)/mouse_sound_commands.c			\
					$(SOUND)/game_sounds.c					\
					$(STATES)/state_death.c					\
					$(STATES)/state_delete_map.c			\
					$(STATES)/state_edition_mode.c			\
					$(STATES)/state_editor.c				\
					$(STATES)/state_editor_menu.c			\
					$(STATES)/state_game.c					\
					$(STATES)/state_get_input.c				\
					$(STATES)/state_get_map_name.c			\
					$(STATES)/state_inputs_settings_menu.c	\
					$(STATES)/state_level_finished.c		\
					$(STATES)/state_main_menu.c				\
					$(STATES)/state_new_highscore.c			\
					$(STATES)/state_pause.c					\
					$(STATES)/state_play_edit_map.c			\
					$(STATES)/state_play_menu.c				\
					$(STATES)/state_sound_settings.c		\
					$(STATES)/state_start.c					\
					$(STATES)/state_scoreboard.c			\
					$(STATES)/state_settings_menu.c			\
					$(STATES)/state_sound_settings.c		\
					$(UI)/convert_to_ppm.c					\
					$(UI)/create_buttons_inputs.c			\
					$(UI)/display_inventory.c				\
					$(UI)/display_inventory_strings.c		\
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
					switch_state.c							\
					utils.c


# **************************************************************************** #
#                                   UTILS                                      #
# **************************************************************************** #

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

DPDCS		= $(OBJS:.o=.d)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all				: $(SDLDIR) SDL_text/ttf_build SDL2_mixer-2.0.4
	@make $(NAME)

$(NAME)			: $(OBJS)

	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -lpthread -lm -ldl -lz -o $@ $^ $(LIBDIR)/libft.a $(LIBSDL)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

-include $(DPDCS)

$(OBJDIR)/%.o	: $(SRCDIR)/%.c | $(OBJDIR)

	@$(CC) $(CFLAGS) $(DEBUG) $(OPTI) $(FSAN) -I $(INCDIR) $(INCSDL) \
		-I $(LIBDIR) -MMD -o $@ -c $<
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(SDLDIR)		:
	sudo apt-get install libasound2-dev libpulse-dev libsdl2-dev
	curl https://www.libsdl.org/release/SDL2-2.0.12.zip --output sdl.zip
	unzip sdl.zip
	rm -rf sdl.zip
	cd $(SDLDIR) && ./configure --prefix $(shell pwd)/$(SDLDIR) && make install

SDL_text/ttf_build	:
	cd SDL_text && tar -xf freetype-2.8.tar.gz
	cd SDL_text && mkdir freetype_build
	cd SDL_text/freetype-2.8 && ./configure --prefix=$(shell pwd)/SDL_text/freetype_build
	make -C SDL_text/freetype-2.8 install
	cd SDL_text && unzip SDL2_ttf-2.0.15.zip
	mkdir SDL_text/ttf_build
	cd SDL_text/SDL2_ttf-2.0.15 && FT2_CONFIG="$(shell pwd)/SDL_text/freetype_build/bin/freetype-config" SDL2_CONFIG="$(shell pwd)/$(SDLDIR)/bin/sdl2-config" && export SDL2_CONFIG && PKG_CONFIG_PATH="$(shell pwd)/SDL_text/freetype_build/lib/pkgconfig/:$(shell pwd)/$(SDLDIR)/lib/pkgconfig/" ./configure --prefix="$(shell pwd)/SDL_text/ttf_build"
	make -C SDL_text/SDL2_ttf-2.0.15 install

SDL_mixer-2.0.4	:
	curl https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.zip --output sdl_mixer.zip
	unzip sdl_mixer.zip
	rm -rf sdl_mixer.zip
	cd SDL2_mixer-2.0.4 SDL2_CONFIG="$(shell pwd)/$(SDLDIR)/bin/sdl2-config" && export SDL2_CONFIG && PKG_CONFIG_PATH="$(shell pwd)/SDL_text/freetype_build/lib/pkgconfig/:$(shell pwd)/$(SDLDIR)/lib/pkgconfig/" && ./configure --prefix $(shell pwd)/SDL2_mixer-2.0.4
	make -C SDL2_mixer-2.0.4 install

$(OBJDIR)		:

	@mkdir -p $@				2> /dev/null || true
	@mkdir -p $@/$(ANIM)		2> /dev/null || true
	@mkdir -p $@/$(CAMERA)		2> /dev/null || true
	@mkdir -p $@/$(EDITOR)		2> /dev/null || true
	@mkdir -p $@/$(GAMEPLAY)	2> /dev/null || true
	@mkdir -p $@/$(MATHS)		2> /dev/null || true
	@mkdir -p $@/$(PROG)		2> /dev/null || true
	@mkdir -p $@/$(RT)			2> /dev/null || true
	@mkdir -p $@/$(SHAPES)		2> /dev/null || true
	@mkdir -p $@/$(SOUND)		2> /dev/null || true
	@mkdir -p $@/$(STATES)		2> /dev/null || true
	@mkdir -p $@/$(UI)			2> /dev/null || true
	@mkdir -p $(SDLDIR)			2>

clean			:

	@rm -rf $(OBJDIR)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"
	@make -C libft clean

fclean			: clean

	@rm -rf $(NAME)
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"
	@rm -rf SDL2-2.0.12 SDL2_mixer-2.0.4 sdl_mixer.zip sdl.zip SDL_text/freetype-2.8 SDL_text/freetype_build SDL_text/SDL2_ttf-2.0.15 SDL_text/ttf_build
	@make -C libft fclean

cm				: clean
	@make all

re				:
	@make fclean
	@make all
.PHONY			: all clean fclean cm re
