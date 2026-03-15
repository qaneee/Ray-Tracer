/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:35:53 by arvardan          #+#    #+#             */
/*   Updated: 2026/01/27 23:02:31 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec_length(t_vec3 vec)
{
	float	len;

	len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (len < 1e-6)
		return (0.0f);
	return (len);
}

t_vec3	normal_vector(t_vec3 vec)
{
	t_vec3	normal;
	float	len;

	len = vec_length(vec);
	if (len < 1e-6)
		return (set_vector(0, 0, 0));
	normal.x = vec.x / len;
	normal.y = vec.y / len;
	normal.z = vec.z / len;
	return (normal);
}

float	point_dist(const t_vec3 *point1, const t_vec3 *point2)
{
	float	dist_x;
	float	dist_y;
	float	dist_z;

	dist_x = (point2->x - point1->x) * (point2->x - point1->x);
	dist_y = (point2->y - point1->y) * (point2->y - point1->y);
	dist_z = (point2->z - point1->z) * (point2->z - point1->z);
	return (sqrtf(dist_x + dist_y + dist_z));
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	vector;

	vector.x = (a.y * b.z - a.z * b.y);
	vector.y = (a.z * b.x - a.x * b.z);
	vector.z = (a.x * b.y - a.y * b.x);
	return (vector);
}

float	dot_product(t_vec3 a, t_vec3 b)
{
	float	val;

	val = a.x * b.x + a.y * b.y + a.z * b.z;
	return (val);
}
