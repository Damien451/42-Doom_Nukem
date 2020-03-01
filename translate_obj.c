/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fjgsjdfgslg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:37:55 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 17:57:55 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

typedef struct s_mesh		t_mesh;
typedef struct s_triangle	t_triangle;
typedef struct s_vec3d		t_vec3d;

struct						s_vec3d
{
	double					x;
	double					y;
	double					z;
};

struct						s_mesh
{
	t_triangle				*triangle;
	long					nbr_vertices;
	long					nbr_triangles;
	t_mesh					*next;
};

struct						s_triangle
{
	t_vec3d					vertices[3];
	t_vec3d					normals[3];
	t_vec3d					textures[3];
	long					attribute;
	t_triangle				*next;
};
typedef struct						tri
{
	t_vec3d					vertices[3];
	t_vec3d					normals[3];
	t_vec3d					textures[3];
}									tri;

int		main(int ac, char **av)
{
	char		*buffer;
	int			i;
	int			j;
	int			k;
	t_triangle	*triangle;
	t_triangle	*start;
	t_vec3d		*vertices;
	t_vec3d		*normals;
	t_vec3d		*tex;

	triangle = NULL;
	buffer = malloc(20000000);
	i = open(av[1], O_RDONLY);
	j = read(i, buffer, 20000000);
	buffer[j] = 0;
	i = 0;
	j = 0;
	k = 0;
	int nbr_triangle = 0;
	vertices = malloc(sizeof(t_vec3d) * 10000); // TODO
	normals = malloc(sizeof(t_vec3d) * 10000); // TODO
	tex = malloc(sizeof(t_vec3d) * 10000); // TODO
	while (*buffer)
	{
		while (isspace(*buffer))
			buffer++;
		if (*buffer == 'v')
		{
			buffer++;
			if (*buffer == ' ')
			{
				vertices[i].x = strtod(buffer, &buffer) + 5;
				vertices[i].y = strtod(buffer, &buffer) + 5;
				vertices[i].z = strtod(buffer, &buffer) + 10;
				i++;
			}
			else if (*buffer == 't')
			{
				buffer++;
				tex[k].x = strtod(buffer, &buffer);
				tex[k].y = strtod(buffer, &buffer);
				k++;
			}
			else if (*buffer == 'n')
			{
				buffer++;
				normals[i].x = strtod(buffer, &buffer);
				normals[i].y = strtod(buffer, &buffer);
				normals[i].z = strtod(buffer, &buffer);
				j++;
			}
		}
		else if (*buffer == 'f')
		{
			buffer += 2;
			if (!triangle)
			{
				triangle = malloc(sizeof(t_triangle));
				start = triangle;
			}
			else
			{
				triangle->next = malloc(sizeof(t_triangle));
				triangle = triangle->next;
			}
			triangle->next = NULL;
			i = strtol(buffer, &buffer, 10);
			buffer++;
			j = strtol(buffer, &buffer, 10);
			triangle->vertices[0] = vertices[i];
			triangle->textures[0] = tex[j];
			i = strtol(buffer, &buffer, 10);
			buffer++;
			j = strtol(buffer, &buffer, 10);
			triangle->vertices[1] = vertices[i];
			triangle->textures[1] = tex[j];
			i = strtol(buffer, &buffer, 10);
			buffer++;
			j = strtol(buffer, &buffer, 10);
			triangle->vertices[2] = vertices[i];
			triangle->textures[2] = tex[j];
			nbr_triangle++;
		}
		else
		{
			while (*buffer && *buffer != '\n')
				buffer++;
			if (*buffer)
				buffer++;
		}
	}
	triangle = start;
	tri *triangl = malloc(sizeof(tri) * nbr_triangle);
	i = 0;
	while (triangle)
	{
		j = 0;
		while (j < 3)
		{
			triangl[i].vertices[j] = triangle->vertices[j];
			triangl[i].normals[j] = triangle->normals[j];
			triangl[i].textures[j] = triangle->textures[j];
			j++;
		}
		i++;
		triangle = triangle->next;
	}
	int fd = open(av[2], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	write(fd, triangl, i * sizeof(tri));
	printf("%d\n", i);
	return (0);
}

