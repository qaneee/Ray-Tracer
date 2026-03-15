/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:27:29 by arvardan          #+#    #+#             */
/*   Updated: 2026/03/12 02:34:17 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_uv_sphere(t_hit *hit)
{
	float	theta;
	float	phi;
	t_vec3	point;

	point = normal_vector(vec_subt(hit->point, hit->objs->pos));
	theta = acosf(-point.y);
	phi = atan2f(-point.z, point.x);
	hit->u = (phi + M_PI) / (2.0f * M_PI);
	hit->v = theta / M_PI;
}

void	calculate_uv_plane(t_hit *hit)
{
	hit->u = fmodf(hit->point.x, 1.0f);
	hit->v = fmodf(hit->point.z, 1.0f);
	if (hit->u < 0.0f)
		hit->u += 1.0f;
	if (hit->v < 0.0f)
		hit->v += 1.0f;
}

void	calculate_uv_cy_co(t_hit *hit)
{
	t_vec3	point;
	float	theta;
	float	height;

	point = vec_subt(hit->point, hit->objs->pos);
	theta = atan2(point.z, point.x);
	hit->u = (theta + M_PI) / (2.0f * M_PI);
	height = dot_product(point, hit->objs->orientation);
	hit->v = (height + hit->objs->height / 2.0f) / hit->objs->height;
}

void	calculate_uv(t_hit *hit)
{
	if (hit->objs->type == PLANE)
		calculate_uv_plane(hit);
	else if (hit->objs->type == SPHERE)
		calculate_uv_sphere(hit);
	else if (hit->objs->type == CYLINDER || hit->objs->type == CONE)
		calculate_uv_cy_co(hit);
}
