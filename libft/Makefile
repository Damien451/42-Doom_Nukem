CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -flto
NAME = libft.a
SRCDIR = ./
INCLDIR = ./
SRCS = $(SRCDIR)ft_atoi.c \
		$(SRCDIR)ft_strtol.c \
		$(SRCDIR)ft_isalnum.c \
		$(SRCDIR)ft_isalpha.c \
		$(SRCDIR)ft_isascii.c \
		$(SRCDIR)ft_isdigit.c \
		$(SRCDIR)ft_isprint.c \
		$(SRCDIR)ft_strlen.c \
		$(SRCDIR)ft_tolower.c \
		$(SRCDIR)ft_toupper.c \
		$(SRCDIR)ft_strcmp.c \
		$(SRCDIR)ft_strncmp.c \
		$(SRCDIR)ft_strcpy.c \
		$(SRCDIR)ft_strncpy.c \
		$(SRCDIR)ft_strcat.c \
		$(SRCDIR)ft_strncat.c \
		$(SRCDIR)ft_strlcat.c \
		$(SRCDIR)ft_strstr.c \
		$(SRCDIR)ft_strnstr.c \
		$(SRCDIR)ft_bzero.c \
		$(SRCDIR)ft_memset.c \
		$(SRCDIR)ft_memcpy.c \
		$(SRCDIR)ft_memccpy.c \
		$(SRCDIR)ft_memchr.c \
		$(SRCDIR)ft_strchr.c \
		$(SRCDIR)ft_strrchr.c \
		$(SRCDIR)ft_memcmp.c \
		$(SRCDIR)ft_memalloc.c \
		$(SRCDIR)ft_memdel.c \
		$(SRCDIR)ft_strnew.c \
		$(SRCDIR)ft_strdel.c \
		$(SRCDIR)ft_strclr.c \
		$(SRCDIR)ft_striter.c \
		$(SRCDIR)ft_striteri.c \
		$(SRCDIR)ft_strmap.c \
		$(SRCDIR)ft_strmapi.c \
		$(SRCDIR)ft_strequ.c \
		$(SRCDIR)ft_strnequ.c \
		$(SRCDIR)ft_strsub.c \
		$(SRCDIR)ft_strjoin.c \
		$(SRCDIR)ft_strtrim.c \
		$(SRCDIR)ft_strsplit.c \
		$(SRCDIR)ft_itoa.c \
		$(SRCDIR)ft_putchar.c \
		$(SRCDIR)ft_putstr.c \
		$(SRCDIR)ft_putendl.c \
		$(SRCDIR)ft_putnbr.c \
		$(SRCDIR)ft_putchar_fd.c \
		$(SRCDIR)ft_putstr_fd.c \
		$(SRCDIR)ft_putendl_fd.c \
		$(SRCDIR)ft_putnbr_fd.c \
		$(SRCDIR)ft_lstnew.c \
		$(SRCDIR)ft_lstdelone.c \
		$(SRCDIR)ft_lstdel.c \
		$(SRCDIR)ft_lstadd.c \
		$(SRCDIR)ft_lstiter.c \
		$(SRCDIR)ft_lstmap.c \
		$(SRCDIR)ft_isspace.c \
		$(SRCDIR)ft_iswhitespace.c \
		$(SRCDIR)ft_memrchr.c \
		$(SRCDIR)ft_strlendl.c \
		$(SRCDIR)queue_forward.c \
		$(SRCDIR)ft_lstadd_back.c \
		$(SRCDIR)queue_new.c \
		$(SRCDIR)queue_add.c\
		$(SRCDIR)ft_realloc.c \
		$(SRCDIR)ft_strrev.c \
		$(SRCDIR)ft_swapchar.c \
		$(SRCDIR)ft_strdup.c \
		$(SRCDIR)ft_memmove.c \
		$(SRCDIR)btree_apply_infix.c \
		$(SRCDIR)btree_apply_prefix.c \
		$(SRCDIR)btree_apply_suffix.c \
		$(SRCDIR)btree_create_node.c \
		$(SRCDIR)btree_insert_data.c \
		$(SRCDIR)btree_search_item.c \
		$(SRCDIR)btree_leaf_count.c \
		$(SRCDIR)btree_level_count.c \
		$(SRCDIR)cocktail_sort_int.c \
		$(SRCDIR)quick_sort_int.c \
		$(SRCDIR)quick_sort_string.c \
		$(SRCDIR)cocktail_sort_string.c \
		$(SRCDIR)free_ptr.c \
		$(SRCDIR)infinity_add.c \
		$(SRCDIR)infinity_mult.c \
		$(SRCDIR)get_next_line.c \
		$(SRCDIR)ft_strfreejoin.c 
OBJS_ = $(SRCS:.c=.o)
OBJS = $(notdir $(OBJS_))

all :
	@make -j $(NAME)

$(NAME) : $(SRCS)
	@make objects
	@ar sucr $(NAME) $(OBJS)
	@echo "\n\033[36mCreation :\033[0m \033[35;3;4m$(NAME)\033[0m\n"

objects : $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c -I $(INCLDIR) $^
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

clean :
	@rm -rf $(OBJS)
	@echo "\n\033[36mDeletion :\033[0m \033[33mObjects\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all objects clean fclean re
