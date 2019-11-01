#include <SDL.h>

int			frame_calculator(void)
{
	static long		frame = 0;
	static long		time = 0;
	long			actual_time;
	long			actual_frame;

	actual_time = SDL_GetTicks();
	if (actual_time - time > 1000)
	{
		actual_frame = frame;
		time = actual_time;
		frame = 0;
		return (actual_frame);
	}
	frame++;
	return (0);
}
