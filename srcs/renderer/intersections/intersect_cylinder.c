/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 01:54:18 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:53:09 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersect_body(t_ray ray, t_objs *cy, float *t)
{
	t_vec3	d_perp;
	t_vec3	co_perp;
	float	t_tmp;
	t_vec3	hit_point;

	perp_component(ray, cy, &d_perp, &co_perp);
	t_tmp = quad_for_cyl(d_perp, co_perp, cy->radius);
	if (t_tmp < 0.0f)
		return (0);
	hit_point = vec_add(ray.origin, vec_scale(ray.direct, t_tmp));
	if (!clampf_height_cy(hit_point, cy))
		return (0);
	*t = t_tmp;
	return (1);
}

static int	intersect_top_disk(t_ray ray, t_objs *cy, float *t)
{
	if (!intersect_plane_at(ray, cy->cap_top_center, cy->orientation, t))
		return (0);
	if (!inside_disk_cy(ray, cy->cap_top_center, cy->radius_sq, *t))
		return (0);
	return (1);
}

static int	intersect_bottom_disk(t_ray ray, t_objs *cy, float *t)
{
	t_vec3	normal;

	normal = vec_scale(cy->orientation, -1.0f);
	if (!intersect_plane_at(ray, cy->cap_bottom_center, normal, t))
		return (0);
	if (!inside_disk_cy(ray, cy->cap_bottom_center, cy->radius_sq, *t))
		return (0);
	return (1);
}

int	intersect_cylinder(t_ray ray, t_objs *cy, float *t)
{
	float	t_min;
	float	t_tmp;

	t_min = INFINITY;
	if (intersect_body(ray, cy, &t_tmp) && t_tmp < t_min)
		t_min = t_tmp;
	if (intersect_top_disk(ray, cy, &t_tmp) && t_tmp < t_min)
		t_min = t_tmp;
	if (intersect_bottom_disk(ray, cy, &t_tmp) && t_tmp < t_min)
		t_min = t_tmp;
	if (t_min == INFINITY)
		return (0);
	*t = t_min;
	return (1);
}
