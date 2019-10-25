#include "doom.h"
#include "graphic_lib.h"

void		load_textures(t_doom *data)
{
	int			i;

	data->lib.character = SDL_LoadBMP("textures/character.bmp");
	data->lib.menu_texture[0] = SDL_LoadBMP("textures/gstvine1.bmp");
	data->lib.menu_texture[1] = SDL_LoadBMP("textures/gstvine2.bmp");
	data->lib.menu_texture[2] = SDL_LoadBMP("enemy_menu.bmp");
	data->lib.menu_texture[3] = SDL_LoadBMP("energy_orb.bmp");
	data->lib.menu_texture[4] = SDL_LoadBMP("textures/background_menu.bmp");
	data->lib.editor_texture = SDL_LoadBMP("textures/editor.bmp");
	data->lib.hud_texture = SDL_LoadBMP("textures/hud.bmp");
	data->lib.skybox[0] = SDL_LoadBMP("textures/hell_rt.bmp");
	data->lib.skybox[1] = SDL_LoadBMP("textures/hell_ft.bmp");
	data->lib.skybox[2] = SDL_LoadBMP("textures/hell_lf.bmp");
	data->lib.skybox[3] = SDL_LoadBMP("textures/hell_bk.bmp");
	data->lib.skybox[4] = SDL_LoadBMP("textures/hell_up.bmp");
	data->lib.skybox[5] = SDL_LoadBMP("textures/hell_dn.bmp");
	i = 0;
	while (i < 6)
	{
		data->lib.skybox_t[i] = SDL_CreateTextureFromSurface(data->lib.renderer, data->lib.skybox[i]);
		i++;
	}
}