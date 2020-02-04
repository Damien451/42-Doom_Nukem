/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/04 22:36:39 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "graphic_lib.h"
#include "inputs.h"
#include "vec3.h"
#include <math.h>

/*void		apply_motion(t_doom *data)
{
	t_vec3d		new_pos;
	double		squat;
	t_vec3d		course;
	static int	frame_s = 0;
	static int	frame_r = 0;

	if (data->lib.cam_keys & SQUAT)
	{
		if (frame_s != 10)
			frame_s++;
	}
	else if (frame_s)
	{
		frame_s -= 2;
		if (frame_s < 0)
			frame_s = 0;
	}
	squat = 0.03 * (data->lib.cam_keys & SQUAT ? 0.10 : 1.0);
	if ((data->lib.cam_keys & COURSE || data->lib.cam_keys & SQUAT) && (data->player.acceleration.x >= squat || data->player.acceleration.x <= -squat || data->player.acceleration.z >= squat || data->player.acceleration.z <= -squat))
	{
		if (frame_r / 12 == 0)
		{
			course = vec3d_scalar(data->player.camera.right, frame_r / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = frame_r * 0.005;
			frame_r++;
		}
		else if (frame_r / 12 == 1)
		{
			course = vec3d_scalar(data->player.camera.right, 1.0 - (frame_r - 12) / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = 12.0 * 0.005 - (frame_r - 12) * 0.005;
			frame_r++;
		}
		else if (frame_r / 12 == 2)
		{
			course = vec3d_scalar(data->player.camera.right, 0.0 - (frame_r - 24) / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = 0.0 - (frame_r - 24) * 0.005;
			frame_r++;
		}
		else
		{
			if (frame_r / 12 == 3)
			{
				course = vec3d_scalar(data->player.camera.right, -1.0 + (frame_r - 36) / 12.0);
				course = vec3d_scalar(course, 0.1);
				course.y = -12.0 * 0.005 + (frame_r - 36) * 0.005;
				frame_r++;
			}
			if (frame_r / 12 == 4)
			{
				course.x = 0;
				course.z = 0;
				course.y = 0;
				frame_r = 0;
			}
		}
	}
	else
	{
		frame_r = 0;
		course.y = 0;
	}*/
//	course = vec3d_add(new_pos, course);
//	course.y += 1.0 - ((double)frame_s * 0.8 / 10.0);
//	check_player_clipping(&data->player.acceleration, &new_pos, data->map_to_save, data->player.position);
//	check_camera_clipping(&data->player.acceleration, &course, data->map_to_save, data->player.position);
//	data->player.camera.origin = course;
//	data->player.position = new_pos;
//}

void			camera_mouse_motion(t_camera *camera, int *x, int *y
		, double *sensitivity)
{
	double	x_angle;
	double	move;

	if (*x)
		rotate_camera(camera, vec3d(0, 1, 0), *sensitivity * (double)*x);
	if (*y)
	{
		move = *sensitivity * (double)*y;
		x_angle = camera->x_angle + move;
		if (x_angle > -1.2 && x_angle < 1.2)
		{
			camera->x_angle = x_angle;
			rotate_camera(camera, camera->right, move);
		}
	}
}

void		clamp_acceleration(t_vec3d *vec, double course)
{
	if (vec->x > 0.5 + course)
		vec->x = 0.5;
	else if (vec->x < -0.5 - course)
		vec->x = -0.5 - course;
	if (vec->y > 1.0 + course)
		vec->y = 1.0 + course;
	if (vec->z > 0.5 + course)
		vec->z = 0.5 + course;
	else if (vec->z < -0.5 - course)
		vec->z = -0.5 - course;
}

void		camera_event_translate(t_doom *data)
{
	t_vec3d		tmp;

	tmp = vec3d_scalar(data->player.acceleration, 0.7);
	if (data->lib.cam_keys & CAMERA_TR_LEFT)
	{
		tmp = vec3d_sub(tmp, vec3d_scalar(data->player.camera.right
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_RIGHT)
	{
		tmp = vec3d_add(tmp, vec3d_scalar(data->player.camera.right
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_FRONT)
	{
		tmp = vec3d_add(tmp, vec3d_scalar(data->player.camera.direction
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_BACK)
	{
		tmp = vec3d_sub(tmp, vec3d_scalar(data->player.camera.direction
					, data->player.speed));
	}
	if (!(data->lib.cam_keys & WATER))
		tmp.y = data->player.acceleration.y - 0.0450;
	clamp_acceleration(&tmp, data->lib.cam_keys & COURSE ? 0.5 : 0);
	data->player.acceleration = tmp;
}

static void	camera_release_key(SDL_Event *event, t_tabinputs *inputs, t_doom *data)
{
	if (event->key.type == SDL_KEYUP)
	{
		if ((unsigned int)event->key.keysym.sym == inputs->keycode[1])
			data->lib.cam_keys &= ~CAMERA_TR_LEFT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[3])
			data->lib.cam_keys &= ~CAMERA_TR_RIGHT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[0])
			data->lib.cam_keys &= ~CAMERA_TR_FRONT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[2])
			data->lib.cam_keys &= ~CAMERA_TR_BACK;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
			data->lib.cam_keys &= ~COURSE;
		else if (event->key.keysym.sym == SDLK_LCTRL)
		{
			data->lib.cam_keys |= SQUAT;
			data->lib.cam_keys &= ~CRAWL;
		}
	}
}

void		camera_press_key(SDL_Event *event, t_tabinputs *inputs, t_doom *data)
{
	data->player.speed = 0.0375 * (data->lib.cam_keys & COURSE ? 2 : 1) * (data->lib.cam_keys & CRAWL ? 0.25 : 1);
	if (event->key.type == SDL_KEYDOWN)
	{
		if ((unsigned int)event->key.keysym.sym == inputs->keycode[1])
			data->lib.cam_keys |= CAMERA_TR_LEFT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[3])
			data->lib.cam_keys |= CAMERA_TR_RIGHT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[0])
			data->lib.cam_keys |= CAMERA_TR_FRONT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[2])
			data->lib.cam_keys |= CAMERA_TR_BACK;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
			data->lib.cam_keys |= COURSE;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[9])
		{
			if (data->player.acceleration.y == 0 && !(data->lib.cam_keys & WATER) && !(data->lib.cam_keys & SQUAT) && !(data->lib.cam_keys & CRAWL))
				data->player.acceleration.y = 0.4;
		}
		else if (event->key.keysym.sym == SDLK_p)
		{
			if (WATER & data->lib.cam_keys)
				data->lib.cam_keys &= ~WATER;
			else
				data->lib.cam_keys |= WATER;
		}
		else if (event->key.keysym.sym == SDLK_LCTRL && data->player.acceleration.y == 0 && !(data->lib.cam_keys & WATER))
			data->lib.cam_keys |= CRAWL;
		else if (event->key.keysym.sym == SDLK_k && !event->key.repeat)
			data->photo = 1;
		else if (event->key.keysym.sym == SDLK_KP_PLUS)
		{
			if (data->player.inventory.selected_block < NBR_TEXTURES_EDITOR)
				data->player.inventory.selected_block++;
			else
				data->player.inventory.selected_block = 1;
		}
		else if (event->key.keysym.sym == SDLK_KP_MINUS)
		{
			if (data->player.inventory.selected_block > 1)
				data->player.inventory.selected_block--;
			else
				data->player.inventory.selected_block = NBR_TEXTURES_EDITOR;
		}
	}
	camera_release_key(event, inputs, data);
}
