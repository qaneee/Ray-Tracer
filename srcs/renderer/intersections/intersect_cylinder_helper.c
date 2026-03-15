/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 02:49:05 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:03 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clampf_height_cy(t_vec3 hit, t_objs *cy)
{
	float	h;

	h = dot_product(vec_subt(hit, cy->pos), cy->orientation);
	if (h < -cy->half_height || h > cy->half_height)
		return (0);
	return (1);
}

void	perp_component(t_ray ray, t_objs *cy, t_vec3 *d_perp, t_vec3 *co_perp)
{
	t_vec3	c_to_o;
	float	proj_da;
	float	proj_coa;

	c_to_o = vec_subt(ray.origin, cy->pos);
	proj_da = dot_product(ray.direct, cy->orientation);
	proj_coa = dot_product(c_to_o, cy->orientation);
	*d_perp = vec_subt(ray.direct, vec_scale(cy->orientation, proj_da));
	*co_perp = vec_subt(c_to_o, vec_scale(cy->orientation, proj_coa));
}

float	quad_for_cyl(t_vec3 d_perp, t_vec3 co_perp, float radius)
{
	float	a;
	float	b;
	float	c;

	a = dot_product(d_perp, d_perp);
	b = 2.0f * dot_product(d_perp, co_perp);
	c = dot_product(co_perp, co_perp) - radius * radius;
	return (ft_quadratic(a, b, c));
}

int	inside_disk_cy(t_ray ray, t_vec3 center, float radius_sq, float t)
{
	t_vec3	hit;

	hit = vec_add(ray.origin, vec_scale(ray.direct, t));
	if (dot_product(vec_subt(hit, center), vec_subt(hit, center)) > radius_sq)
		return (0);
	return (1);
}

int	intersect_plane_at(t_ray ray, t_vec3 center, t_vec3 normal, float *t)
{
	float	denom;
	t_vec3	p0_to_o;

	denom = dot_product(ray.direct, normal);
	if (fabsf(denom) < 1e-6f)
		return (0);
	p0_to_o = vec_subt(center, ray.origin);
	*t = dot_product(p0_to_o, normal) / denom;
	if (*t < EPS)
		return (0);
	return (1);
}
