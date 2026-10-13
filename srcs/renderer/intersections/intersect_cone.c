/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 03:41:03 by arvardan          #+#    #+#             */
/*   Updated: 2026/10/14 02:01:58 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cone_roots(t_ray ray, t_objs *co, float *t0, float *t1)
{
	t_vec3	v;
	float	q[6];

	v = vec_subt(ray.origin, co->pos);
	q[0] = dot_product(ray.direct, co->orientation);
	q[1] = dot_product(v, co->orientation);
	q[2] = q[0] * q[0] - co->cone_k * dot_product(ray.direct, ray.direct);
	q[3] = 2.0f * (q[0] * q[1] - co->cone_k * dot_product(ray.direct, v));
	q[4] = q[1] * q[1] - co->cone_k * dot_product(v, v);
	if (fabsf(q[2]) < 1e-6f)
	{
		if (fabsf(q[3]) < 1e-6f)
			return (0);
		return (*t0 = -q[4] / q[3], *t1 = *t0, 1);
	}
	q[5] = q[3] * q[3] - 4.0f * q[2] * q[4];
	if (q[5] < 0.0f)
		return (0);
	q[5] = sqrtf(q[5]);
	q[0] = (-q[3] - q[5]) / (2.0f * q[2]);
	q[1] = (-q[3] + q[5]) / (2.0f * q[2]);
	return (*t0 = fminf(q[0], q[1]), *t1 = fmaxf(q[0], q[1]), 1);
}

static int	cone_root_ok(t_ray ray, t_objs *co, float t)
{
	t_vec3	hit;
	float	height;

	if (t < EPS)
		return (0);
	hit = vec_add(ray.origin, vec_scale(ray.direct, t));
	height = dot_product(vec_subt(hit, co->pos), co->orientation);
	return (height >= 0.0f && height <= co->height);
}

static int	intersect_cone_body(t_ray ray, t_objs *co, float *t)
{
	float	t0;
	float	t1;

	if (!cone_roots(ray, co, &t0, &t1))
		return (0);
	if (cone_root_ok(ray, co, t0))
		return (*t = t0, 1);
	if (cone_root_ok(ray, co, t1))
		return (*t = t1, 1);
	return (0);
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
