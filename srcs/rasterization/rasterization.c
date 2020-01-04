/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:01:14 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/04 19:38:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterization.h"

t_vec2d			perspective_proj(t_vec3d vertex, double matrix[4][4])
{
	t_vec2d	projected;
	t_vec3d	new;

	new.x = vertex.x * matrix[0][0] + vertex.y * matrix[1][0]
		+ vertex.z * matrix[2][0] + matrix[3][0];
	new.y = vertex.x * matrix[0][1] + vertex.y * matrix[1][1]
		+ vertex.z * matrix[2][1] + matrix[3][1];
	new.z = vertex.x * matrix[0][2] + vertex.y * matrix[1][2]
		+ vertex.z * matrix[2][2] + matrix[3][2];
	projected.x = new.x / new.z;
	projected.y = new.y / new.z;
	return (projected);
}

int			create_bounding_box(t_vec2d vertices[3], t_vec2d bbox[2])
{
	int			i;

	bbox[0].x = -INFINITY;
	bbox[0].y = -INFINITY;
	bbox[1].x = INFINITY;
	bbox[1].y = INFINITY;
	i = 0;
	while (i < 3)
	{
		if (vertices[i].x < bbox[0].x)
			bbox[0].x = vertices[i].x;
		if (vertices[i].x > bbox[1].x)
			bbox[1].x = vertices[i].x;
		if (vertices[i].y < bbox[0].y)
			bbox[0].y = vertices[i].y;
		if (vertices[i].y > bbox[1].y)
			bbox[1].y = vertices[i].y;
		i++;
	}
	return (0);
}

int			loop_over_bounding_box(t_vec2d vertices[3], t_vec2d bbox[2]
	, double *z_buffer, unsigned int *image)
{
	t_vec2l		min;
	t_vec2l		max;
	double		distance;

	min.x = bbox[0].x;
	if (min.x < 0)
		min.x = 0;
	max.x = bbox[1].x + 1;
	max.y = bbox[1].y + 1;
	if (max.x >= WIDTH)
		max.x = WIDTH - 1;
	if (max.y >= HEIGHT)
		max.y = HEIGHT - 1;
	while (min.x <= max.x)
	{
		min.y = bbox[0].y;
		if (min.y < 0)
			min.y = 0;
		while (min.y <= max.y)
		{
			if (THE_TRIANGLE_IS_INSIDE_THE_PIXEL)
			{
				distance = CALCUL_DISTANCE_BETWEEN_CAMERA_AND_POINT;
				if (distance < z_buffer[min.x * WIDTH + min.y])
				{
					z_buffer[min.x * WIDTH + min.y] = distance;
					image[min.x * WIDTH + min.y] = FIND_COLOR_IN_TRIANGLE;
				}
			}
			min.y++;
		}
		min.x++;
	}
	return (0);
}

int			convert_camera_to_matrix44(t_camera *camera, double matrix[4][4])
{
	matrix[0][0] = camera->direction.x;
	matrix[0][1] = camera->direction.y;
	matrix[0][2] = camera->direction.z;
	matrix[1][0] = camera->up.x;
	matrix[1][1] = camera->up.y;
	matrix[1][2] = camera->up.z;
	matrix[2][0] = camera->right.x;
	matrix[2][1] = camera->right.y;
	matrix[2][2] = camera->right.z;
	matrix[3][0] = camera->position.x;
	matrix[3][1] = camera->position.y;
	matrix[3][2] = camera->position.z;
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;
	return (0);
}

int			rasterization(t_doom *data, t_mesh *meshes)
{
	int				i;
	t_vec2d			vertices[3];
	t_vec2d			bbox[2];
	t_mesh			*obj;
	t_triangle		*triangle;
	double			world_to_camera[4][4];
	double			camera_to_world[4][4];

	convert_camera_to_matrix44(&data->player.camera, camera_to_world);
	matrix44_inverse(camera_to_world, world_to_camera);
	obj = meshes;
	while (obj)
	{
		triangle = obj.triangle;
		while (triangle)
		{
			vertices[0] = perspective_proj(triangle.vertices[0], world_to_camera);
			vertices[1] = perspective_proj(triangle.vertices[1], world_to_camera);
			vertices[2] = perspective_proj(triangle.vertices[2], world_to_camera);
			create_bounding_box(vertices, bbox);
			loop_over_bounding_box(vertices, bbox);
			triangle = triangle->next;
		}
		obj = obj->next;
	}
}
