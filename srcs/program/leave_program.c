#include "doom.h"
#include "graphic_lib.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <inputs.h>
#include "libft.h"
#include "octree.h"

static void	close_fonts(t_doom *data)
{
	int i;

	i = 0;
	while (++i <= NBR_FONTS)
		TTF_CloseFont(data->lib.ptrfont[NBR_FONTS - i]);
	if (TTF_WasInit() == 1)
		TTF_Quit();
}

void		free_octree(t_octree *node)
{
	int			i;

	i = 0;
	if (node)
	{
		while (i < 8)
			free_octree(node->child[i++]);
		free(node);
		node = NULL;
	}
}

int			leave_program(t_doom *data, int type)
{
	free_octree(data->octree);
	if (data->lib.texture)
		SDL_DestroyTexture(data->lib.texture);
	if (data->lib.renderer)
		SDL_DestroyRenderer(data->lib.renderer);
	if (data->lib.window)
		SDL_DestroyWindow(data->lib.window);
	close_fonts(data);
	SDL_Quit();
	return (type);
}
