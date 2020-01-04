#include "graphic_lib.h"

static inline void	init_map_colors2(t_graphic_lib *lib)
{
	lib->map_colors[21] = 0x661813;
	lib->map_colors[22] = 0x46241d;
	lib->map_colors[23] = 0x898280;
	lib->map_colors[24] = 0xd3d3d3;
	lib->map_colors[25] = 0xd3d3d3;
	lib->map_colors[26] = 0xd3d3d3;
	lib->map_colors[27] = 0x8b8b8b;
	lib->map_colors[28] = 0xffffff;
	lib->map_colors[29] = 0x2f2d3d;
	lib->map_colors[30] = 0x971a28;
	lib->map_colors[31] = 0x276107;
	lib->map_colors[32] = 0x078eae;
	lib->map_colors[33] = 0xf6ce78;
	lib->map_colors[34] = 0x7c7c86;
	lib->map_colors[35] = 0x5b4526;
	lib->map_colors[36] = 0xe0b378;
	lib->map_colors[37] = 0x352916;
	lib->map_colors[38] = 0x2f241b;
	lib->map_colors[39] = 0x41291e;
	lib->map_colors[40] = 0xffffff;
}

void				init_map_colors(t_graphic_lib *lib)
{
	lib->map_colors[0] = 0x585949;
	lib->map_colors[1] = 0x7b716e;
	lib->map_colors[2] = 0x8c8174;
	lib->map_colors[3] = 0xbcbcb9;
	lib->map_colors[4] = 0x956250;
	lib->map_colors[5] = 0xc3a58a;
	lib->map_colors[6] = 0xcfb48f;
	lib->map_colors[7] = 0xcfb48f;
	lib->map_colors[8] = 0xcfb48f;
	lib->map_colors[9] = 0xcfb48f;
	lib->map_colors[10] = 0x525252;
	lib->map_colors[11] = 0x525252;
	lib->map_colors[12] = 0x989898;
	lib->map_colors[13] = 0x686a6f;
	lib->map_colors[14] = 0x33332f;
	lib->map_colors[15] = 0x33332f;
	lib->map_colors[16] = 0x33332f;
	lib->map_colors[17] = 0x93908e;
	lib->map_colors[18] = 0x656261;
	lib->map_colors[19] = 0x656261;
	lib->map_colors[20] = 0x989898;
	init_map_colors2(lib);
}