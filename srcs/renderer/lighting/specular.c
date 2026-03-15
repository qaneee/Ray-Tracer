/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:54:38 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/15 17:05:29 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	vec_reflect_p(t_vec3 incident, t_vec3 normal)
{
	float	dot;

	dot = dot_product(incident, normal);
	return (vec_subt(vec_scale(normal, 2.0f * dot), incident));
}

static float	specular_intensity(t_scene *sc, t_hit *hit,
		t_light *light, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_vec;
	float	distance;
	float	intensity;

	light_dir = vec_subt(light->pos, hit->point);
	distance = vec_length(light_dir);
	light_dir = normal_vector(light_dir);
	if (is_in_shadow(sc, hit->point, light_dir, distance))
		return (0.0f);
	reflect_vec = vec_reflect_p(light_dir, hit->normal);
	intensity = fmaxf(0.0f, dot_product(reflect_vec, view_dir));
	return (powf(intensity, hit->objs->shininess)
		* light->brightness * hit->objs->specular);
}

t_color	calc_specular(t_scene *sc, t_hit *hit, t_vec3 view_pos)
{
	t_color	result;
	t_light	*light;
	t_vec3	view_dir;
	float	intensity;

	if (hit->objs->specular <= 0.0f)
		return ((t_color){0, 0, 0});
	result = (t_color){0, 0, 0};
	view_dir = normal_vector(vec_subt(view_pos, hit->point));
	light = sc->lights;
	while (light)
	{
		intensity = specular_intensity(sc, hit, light, view_dir);
		result.r += intensity * light->color.r;
		result.g += intensity * light->color.g;
		result.b += intensity * light->color.b;
		light = light->next;
	}
	return (result);
}
