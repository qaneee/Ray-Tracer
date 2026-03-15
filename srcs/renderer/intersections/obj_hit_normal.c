/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_hit_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:26:55 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:53:24 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	normal_sphere(t_hit *hit)
{
	return (normal_vector(vec_subt(hit->point, hit->objs->pos)));
}

static t_vec3	normal_plane(t_hit *hit)
{
	return (hit->objs->orientation);
}

static t_vec3	normal_cylinder(t_hit *hit)
{
	t_vec3	cap_normal;
	t_vec3	axis_to_point;
	float	projection;

	if (cylinder_cap_normal(hit, &cap_normal))
		return (cap_normal);
	axis_to_point = vec_subt(hit->point, hit->objs->pos);
	projection = dot_product(axis_to_point, hit->objs->orientation);
	return (normal_vector(vec_subt(axis_to_point,
				vec_scale(hit->objs->orientation, projection))));
}

static t_vec3	normal_cone(t_hit *hit)
{
	t_vec3	cap_normal;

	if (cone_base_normal(hit, &cap_normal))
		return (cap_normal);
	return (cone_side_normal(hit));
}

void	calculate_normal(t_hit *hit)
{
	if (hit->objs->type == SPHERE)
		hit->normal = normal_sphere(hit);
	else if (hit->objs->type == PLANE)
		hit->normal = normal_plane(hit);
	else if (hit->objs->type == CYLINDER)
		hit->normal = normal_cylinder(hit);
	else if (hit->objs->type == CONE)
		hit->normal = normal_cone(hit);
	hit->normal = normal_vector(hit->normal);
	if (hit->objs->checkerboard || hit->objs->texture)
		calculate_uv(hit);
	if (hit->objs->texture)
		hit->normal = perturb_normal(hit);
}
