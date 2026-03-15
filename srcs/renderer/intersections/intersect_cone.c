/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 03:41:03 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:52 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	quad_for_cone(t_ray ray, t_objs *co)
{
	t_vec3	v;
	float	a;
	float	b;
	float	c;

	v = vec_subt(ray.origin, co->pos);
	a = dot_product(ray.direct, co->orientation);
	b = dot_product(v, co->orientation);
	c = a * a - co->cone_k;
	a = 2.0f * (a * b - co->cone_k * dot_product(ray.direct, v));
	b = b * b - co->cone_k * dot_product(v, v);
	return (ft_quadratic(c, a, b));
}

static int	clampf_cone_height(t_vec3 hit, t_objs *co)
{
	float	height;

	height = dot_product(vec_subt(hit, co->pos), co->orientation);
	if (height < 0.0f || height > co->height)
		return (0);
	return (1);
}

static int	intersect_cone_body(t_ray ray, t_objs *co, float *t)
{
	float	t_tmp;
	t_vec3	hit;

	t_tmp = quad_for_cone(ray, co);
	if (t_tmp < 0.0f)
		return (0);
	hit = vec_add(ray.origin, vec_scale(ray.direct, t_tmp));
	if (!clampf_cone_height(hit, co))
		return (0);
	*t = t_tmp;
	return (1);
}

static int	cone_base_disk(t_ray ray, t_objs *co, float *t)
{
	t_vec3	p0_to_o;
	t_vec3	hit;
	float	denom;

	denom = dot_product(ray.direct, co->orientation);
	if (fabsf(denom) < 1e-6f)
		return (0);
	p0_to_o = vec_subt(co->cone_base_center, ray.origin);
	*t = dot_product(p0_to_o, co->orientation) / denom;
	if (*t < EPS)
		return (0);
	hit = vec_add(ray.origin, vec_scale(ray.direct, *t));
	if (dot_product(vec_subt(hit, co->cone_base_center),
			vec_subt(hit, co->cone_base_center)) > co->radius_sq)
		return (0);
	return (1);
}

int	intersect_cone(t_ray ray, t_objs *co, float *t)
{
	float	t_min;
	float	t_tmp;

	t_min = INFINITY;
	if (intersect_cone_body(ray, co, &t_tmp) && t_tmp < t_min)
		t_min = t_tmp;
	if (cone_base_disk(ray, co, &t_tmp) && t_tmp < t_min)
		t_min = t_tmp;
	if (t_min == INFINITY)
		return (0);
	*t = t_min;
	return (1);
}
