# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/11 00:37:10 by roduquen          #+#    #+#              #
#    Updated: 2019/09/19 17:06:33 by dacuvill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

LOGIN = `whoami`

CFLAGS = -Wall -Wextra -Werror -Ofast #-g3

NAME = doom-nukem

SRCDIR = ./srcs/

OBJDIR = ./obj/

INCLDIR = ./includes/

LIBDIR = ./libft/

LIB = $(LIBDIR)libft.a

LIBSDL = -L /Users/$(LOGIN)/.brew/lib/ -lSDL2-2.0.0 -lSDL2_ttf-2.0.0 -lSDL2_image-2.0.0 `sdl2-config --cflags --libs`

SRCS =	$(SRCDIR)add_points.c				\
		$(SRCDIR)doom.c						\
		$(SRCDIR)draw_rectangle.c			\
		$(SRCDIR)frame_calculator.c			\
		$(SRCDIR)game_main_menu.c			\
		$(SRCDIR)game_start.c				\
		$(SRCDIR)init_program.c				\
		$(SRCDIR)leave_program.c			\
		$(SRCDIR)parse_input_dict.c			\
		$(SRCDIR)program.c					\
		$(SRCDIR)put_buttons_names.c		\
		$(SRCDIR)put_buttons_on_img.c		\
		$(SRCDIR)put_string_on_renderer.c	\
		$(SRCDIR)settings_menu.c			\
		$(SRCDIR)utils.c					\
		$(SRCDIR)vec3l_maths.c				\
		$(SRCDIR)vec3d_maths.c				\
		$(SRCDIR)vec3l_maths_2.c			\
		$(SRCDIR)vec3d_maths_2.c			\
		$(SRCDIR)free_tabinputs.c

OBJ = $(notdir $(SRCS:.c=.o))

OBJS = $(addprefix $(OBJDIR),$(OBJ))

DPDCS = $(OBJS:.o=.d)

all :
	@mkdir -p $(OBJDIR)
	@make -j $(NAME)

$(NAME) : $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) $(OBJS) -o $@ -L $(LIBDIR) -lft $(LIBSDL)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $^ -I $(INCLDIR) -I /Users/$(LOGIN)/.brew/include/SDL2 -o $@
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(LIB) :
	@echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	@make -C libft

clean :
	@rm -rf $(OBJDIR)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

cm : clean all

fclean : clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all clean fclean re cm
