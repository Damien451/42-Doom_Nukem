/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 15:40:44 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/05 18:50:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

int		matrix44_vec3d_mul(double matrix[4][4], t_vec3d src, t_vec3d *result)
{
	double		tmp[4];

	tmp[0] = src.x * matrix[0][0] + src.y * matrix[1][0] + src.z * matrix[2][0]
		+ matrix[3][0];
	tmp[1] = src.x * matrix[0][1] + src.y * matrix[1][1] + src.z * matrix[2][1]
		+ matrix[3][1];
	tmp[2] = src.x * matrix[0][2] + src.y * matrix[1][2] + src.z * matrix[2][2]
		+ matrix[3][2];
	tmp[3] = src.x * matrix[0][3] + src.y * matrix[1][3] + src.z * matrix[2][3]
		+ matrix[3][3];
	result->x = tmp[0];
	result->y = tmp[1];
	result->z = tmp[2];
	return (0);
}

int		matrix44_identity(double result[4][4])
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = 0;
			if (i == j)
				result[i][j] = 1;
			j++;
		}
		i++;
	}
	return (0);
}

void	swap_values(double *x, double *y)
{
	double		tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

int		matrix44_inverse(const double matrix[4][4], double result[4][4])
{
	double		tmp[4][4];
	int			cnt[3];
	int			size[2];
	double		value;

	matrix44_identity(result);
	cnt[0] = 0;
	while (cnt[0] < 4)
	{
		cnt[1] = 0;
		while (cnt[1] < 4)
		{
			tmp[cnt[0]][cnt[1]] = matrix[cnt[0]][cnt[1]];
			cnt[1]++;
		}
		cnt[0]++;
	}
	cnt[0] = -1;
	while (++cnt[0] < 4)
	{
		/*
		** SWAP IF PIVOT IS NOT WORKING
		*/
		if (tmp[cnt[0]][cnt[0]] == 0)
		{
			size[0] = cnt[0];
			cnt[1] = -1;
			while (++cnt[1] < 4)
			{
				if (fabs(tmp[cnt[1]][cnt[0]]) > fabs(tmp[size[0]][cnt[0]]))
					size[0] = cnt[1];
			}
			// SINGULAR MATRIX
			if (size[0] == cnt[0])
				return (1);
			cnt[1] = -1;
			while (++cnt[1] < 4)
			{
				swap_values(&tmp[cnt[0]][cnt[1]], &tmp[size[0]][cnt[1]]);
				swap_values(&result[cnt[0]][cnt[1]], &result[size[0]][cnt[1]]);
			}
		}
		// SET COLUMN TO 0
		cnt[1] = -1;
		while (++cnt[1] < 4)
		{
			if (cnt[1] != cnt[0])
			{
				value = tmp[cnt[1]][cnt[0]] / tmp[cnt[0]][cnt[0]];
				if (value)
				{
					cnt[2] = -1;
					while (++cnt[2] < 4)
					{
						tmp[cnt[1]][cnt[2]] -= value * tmp[cnt[0]][cnt[2]];
						result[cnt[1]][cnt[2]] -= value * result[cnt[0]][cnt[2]];
					}
					tmp[cnt[1]][cnt[0]] = 0;
				}
			}
		}
	}
	cnt[0] = -1;
	while (++cnt[0] < 4)
	{
		cnt[1] = -1;
		while (++cnt[1] < 4)
		{
			result[cnt[0]][cnt[1]] /= tmp[cnt[0]][cnt[0]];
		}
	}
	return (0);
}

/*

int		matrix44_inverse(const double matrix[4][4], double result[4][4])
{
	double		tmp[4][4];
	int			cnt[3];
	int			pivot;
	double		size[2];

	matrix44_identity(result);
	cnt[0] = 0;
	while (cnt[0] < 4)
	{
		cnt[1] = 0;
		while (cnt[1] < 4)
		{
			tmp[cnt[0]][cnt[1]] = matrix[cnt[0]][cnt[1]];
			cnt[1]++;
		}
		cnt[0]++;
	}
	cnt[0] = 0;
	while (cnt[0] < 3)
	{
		pivot = cnt[0];
		size[0] = tmp[cnt[0]][cnt[0]];
		if (size[0] < 0)
			size[0] = -size[0];
		cnt[1] = cnt[0] + 1;
		while (cnt[1] < 4)
		{
			size[1] = tmp[cnt[1]][cnt[0]];
			if (size[1] < 0)
				size[1] = -size[1];
			if (size[1] > size[0])
			{
				pivot = cnt[1];
				size[0] = size[1];
			}
			cnt[1]++;
		}
		if (!size[0])
			return (1);
		if (pivot != cnt[0])
		{
			cnt[1] = 0;
			while (cnt[1] < 4)
			{
				size[1] = tmp[cnt[0]][cnt[1]];
				tmp[cnt[0]][cnt[1]] = tmp[pivot][cnt[1]];
				tmp[pivot][cnt[1]] = size[1];
				size[1] = result[cnt[0]][cnt[1]];
				result[cnt[0]][cnt[1]] = result[pivot][cnt[1]];
				result[pivot][cnt[1]] = size[1];
				cnt[1]++;
			}
			cnt[1] = cnt[0] + 1;
			while (cnt[1] < 4)
			{
				size[1] = tmp[cnt[1]][cnt[0]] / tmp[cnt[0]][cnt[0]];
				cnt[2] = 0;
				while (cnt[2] < 4)
				{
					tmp[cnt[1]][cnt[2]] -= (size[1] * tmp[cnt[0]][cnt[2]]);
					result[cnt[1]][cnt[2]] -= (size[1] * result[cnt[0]][cnt[2]]);
					cnt[2]++;
				}
				tmp[cnt[1]][cnt[0]] = 0;
				cnt[1]++;
			}
		}
		cnt[0]++;
	}
	cnt[0] = 3;
	while (cnt[0] >= 0)
	{
		size[1] = tmp[cnt[0]][cnt[0]];
		if (!size[1])
			return (1);
		cnt[1] = 0;
		while (cnt[1] < 4)
		{
			tmp[cnt[0]][cnt[1]] /= size[1];
			result[cnt[0]][cnt[1]] /= size[1];
			cnt[1]++;
		}
		cnt[1] = 0;
		while (cnt[1] < cnt[0])
		{
			size[1] = tmp[cnt[1]][cnt[0]];
			cnt[2] = 0;
			while (cnt[2] < 4)
			{
				tmp[cnt[1]][cnt[2]] -= (size[1] * tmp[cnt[0]][cnt[2]]);
				result[cnt[1]][cnt[2]] -= (size[1] * result[cnt[0]][cnt[2]]);
				cnt[2]++;
			}
			cnt[1]++;
		}
		cnt[0]--;
	}
	cnt[0] = 0;
	while (cnt[0] < 4)
	{
		cnt[1] = 0;
		while (cnt[1] < 4)
		{
			printf("% .2f", tmp[cnt[0]][cnt[1]]);
			cnt[1]++;
		}
		printf("\n");
		cnt[0]++;
	}
	return (0);
}*/

int		matrix44_multiply(const double a[4][4], const double b[4][4]
	, double result[4][4])
{
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j]
				+ a[i][2] * b[2][j] + a[i][3] * b[3][j];
			j++;
		}
		i++;
	}
	return (0);
}
