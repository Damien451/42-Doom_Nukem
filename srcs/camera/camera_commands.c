/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/24 19:01:11 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "vec3.h"
#include <math.h>

void			camera_mouse_motion(t_camera *camera, int *x, int *y
	, double *sensitivity)
{
	double	x_angle;
	double	move;

	if (*x)
		rotate_camera(camera, Y_AXIS, *sensitivity * (double)*x);
	if (*y)
	{
		move = *sensitivity * (double)*y;
		x_angle = camera->x_angle + move;
		if (x_angle > -1 && x_angle < 1)
		{
			camera->x_angle = x_angle;
			rotate_camera(camera, camera->right, move);
		}
	}
}

static void	check_clipping(t_doom *data, int type)
{
	type++;
	if (data->player.camera.origin.x > 64)
		data->player.camera.origin.x = 64;
	if (data->player.camera.origin.y > 64)
		data->player.camera.origin.y = 64;
	if (data->player.camera.origin.z > 64)
		data->player.camera.origin.z = 64;
	if (data->player.camera.origin.x < 0)
		data->player.camera.origin.x = 0;
	if (data->player.camera.origin.y < 0)
		data->player.camera.origin.y = 0;
	if (data->player.camera.origin.z < 0)
		data->player.camera.origin.z = 0;
}

void		camera_event_translate(t_doom *data)
{
	double		speed_up;
	int			stop;
	static int	frame = 0;
	static double	y_max = 0;
	double			diviseur;

	data->player.gravity += 9.8 / 1000 / (data->lib.cam_keys & WATER ? 10 : 1);
	diviseur = data->lib.cam_keys & WATER ? 2 : 1;
	diviseur *= data->lib.cam_keys & SQUAT ? 1.5 : 1;
	if (y_max < data->player.camera.origin.y)
	{
		y_max = data->player.camera.origin.y;
//		printf("max size = %f\n", y_max);
	}
//	else if (y_max != 0 && data->player.camera.origin.y != 1)
	//	printf("pos      = %f\n", data->player.camera.origin.y);
	if (data->player.camera.origin.y == 1)
	{
//		if (frame != 1)
//			printf("frame = %d\n", frame);
		frame = 0;
	}
	frame++;
	speed_up = data->player.speed + (ACCELERATION * ((data->lib.cam_keys & COURSE) >> 4) / 3.0 + ACCELERATION) / diviseur;
	stop = 1;
	if (speed_up > (MAX_SPEED + MAX_SPEED * ((data->lib.cam_keys & COURSE) >> 4) / 3.0) / diviseur)
		speed_up = (MAX_SPEED + MAX_SPEED * ((data->lib.cam_keys & COURSE) >> 4) / 3.0) / diviseur;
	if (data->lib.cam_keys & CAMERA_TR_LEFT)
	{
		data->player.speed = speed_up;
		data->player.camera.origin = vec3d_sub(data->player.camera.origin
				, vec3d_scalar(data->player.camera.right, data->player.speed));
		check_clipping(data, CAMERA_TR_LEFT);
		stop = 0;
	}
	if (data->lib.cam_keys & CAMERA_TR_RIGHT)
	{
		data->player.speed = speed_up;
		data->player.camera.origin = vec3d_add(data->player.camera.origin
				, vec3d_scalar(data->player.camera.right, data->player.speed));
		check_clipping(data, CAMERA_TR_RIGHT);
		stop = 0;
	}
	if (data->lib.cam_keys & CAMERA_TR_FRONT)
	{
		data->player.speed = speed_up;
		data->player.camera.origin = vec3d_add(data->player.camera.origin
				, vec3d_scalar(data->player.camera.direction, data->player.speed));
		check_clipping(data, CAMERA_TR_FRONT);
		stop = 0;
	}
	if (data->lib.cam_keys & CAMERA_TR_BACK)
	{
		data->player.speed = speed_up;
		data->player.camera.origin = vec3d_sub(data->player.camera.origin
				, vec3d_scalar(data->player.camera.direction, data->player.speed));
		check_clipping(data, CAMERA_TR_BACK);
		stop = 0;
	}
	if (data->lib.cam_keys & WATER)
	{
		if (data->player.gravity > 0.01)
			data->player.gravity = 0.01;
	}
	data->player.camera.origin.y -= data->player.gravity;
	if (data->player.camera.origin.y < 1)
	{
		data->player.gravity = GRAVITY;
		data->player.camera.origin.y = 1;
	}
//	printf("data->player.camera.origin.y = %.2f, data->player.gravity = %.2f\n"
//		,data->player.camera.origin.y, data->player.gravity);
	if (data->lib.cam_keys & SQUAT)
	{
		data->player.speed = 0.04;
		data->player.camera.origin.y -= 0.5;
	}
//	printf("vitesse = %f\n", data->player.speed);
	if (stop)
		data->player.speed = 0;
}

static void	camera_release_key(SDL_Event *event, t_doom *data)
{
	if (event->key.type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys &= ~CAMERA_TR_LEFT;
		else if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys &= ~CAMERA_TR_RIGHT;
		else if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys &= ~CAMERA_TR_FRONT;
		else if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys &= ~CAMERA_TR_BACK;
		else if (event->key.keysym.sym == SDLK_LSHIFT)
			data->lib.cam_keys &= ~COURSE;
		else if (event->key.keysym.sym == SDLK_LCTRL)
			data->lib.cam_keys &= ~SQUAT;
	}
}

void		camera_press_key(SDL_Event *event, t_doom *data)
{
	if (event->key.type == SDL_KEYDOWN)
	{

		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys |= CAMERA_TR_LEFT;
		else if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys |= CAMERA_TR_RIGHT;
		else if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys |= CAMERA_TR_FRONT;
		else if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys |= CAMERA_TR_BACK;
		else if (event->key.keysym.sym == SDLK_LSHIFT)
			data->lib.cam_keys |= COURSE;
		else if (event->key.keysym.sym == SDLK_SPACE
			&& data->player.gravity == GRAVITY && !(data->lib.cam_keys & WATER))
			data->player.gravity = -0.18 * GRAVITY;
		else if (event->key.keysym.sym == SDLK_p)
		{
			if (WATER & data->lib.cam_keys)
				data->lib.cam_keys &= ~WATER;
			else
				data->lib.cam_keys |= WATER;
		}
		else if (event->key.keysym.sym == SDLK_LCTRL)
			data->lib.cam_keys |= SQUAT;
	}
	camera_release_key(event, data);
}
