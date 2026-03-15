/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:02:44 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:37 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	vec_reflect(t_vec3 incident, t_vec3 normal)
{
	float	dot;

	dot = dot_product(incident, normal);
	return (vec_subt(incident, vec_scale(normal, 2.0f * dot)));
}

t_color	get_reflect_vec(t_scene *sc, t_hit *hit, t_ray *incoming, int depth)
{
	t_vec3	reflect_vec;
	t_ray	reflect_ray;

	reflect_vec = vec_reflect(incoming->direct, hit->normal);
	reflect_ray.origin = vec_add(hit->point, vec_scale(reflect_vec, EPS));
	reflect_ray.direct = reflect_vec;
	return (trace_ray(sc, &reflect_ray, depth));
}

t_color	blend_color(t_color base, t_color reflect, float ref_coef)
{
	t_color	final_color;

	final_color.r = base.r * (1.0f - ref_coef) + reflect.r * ref_coef;
	final_color.g = base.g * (1.0f - ref_coef) + reflect.g * ref_coef;
	final_color.b = base.b * (1.0f - ref_coef) + reflect.b * ref_coef;
	return (final_color);
}
