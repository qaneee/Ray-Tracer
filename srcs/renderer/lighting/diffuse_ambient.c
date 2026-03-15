/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:16:26 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/11 00:39:27 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	calc_ambient(t_scene *sc, t_color obj_color)
{
	t_color	amb_res;

	amb_res.r = (sc->amb.ratio * sc->amb.color.r * obj_color.r) / 255;
	amb_res.g = (sc->amb.ratio * sc->amb.color.g * obj_color.g) / 255;
	amb_res.b = (sc->amb.ratio * sc->amb.color.b * obj_color.b) / 255;
	return (amb_res);
}

t_color	calc_diffuse(t_scene *sc, t_hit *hit)
{
	t_light	*lights;
	t_color	result;
	t_vec3	light_dir;
	float	intensity;
	float	light_dot;

	result = (t_color){0, 0, 0};
	lights = sc->lights;
	while (lights)
	{
		light_dir = vec_subt(lights->pos, hit->point);
		if (!is_in_shadow(sc, hit->point, normal_vector(light_dir),
				vec_length(light_dir)))
		{
			light_dot = dot_product(hit->normal, normal_vector(light_dir));
			intensity = fmaxf(0.0f, light_dot) * lights->brightness;
			result.r += intensity * lights->color.r * hit->color.r / 255;
			result.g += intensity * lights->color.g * hit->color.g / 255;
			result.b += intensity * lights->color.b * hit->color.b / 255;
		}
		lights = lights->next;
	}
	return (result);
}

t_color	combine_lighting(t_scene *sc, t_hit *hit, t_vec3 view_pos)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	res;

	ambient = calc_ambient(sc, hit->color);
	diffuse = calc_diffuse(sc, hit);
	specular = calc_specular(sc, hit, view_pos);
	res.r = fminf(255, ambient.r + diffuse.r + specular.r);
	res.g = fminf(255, ambient.g + diffuse.g + specular.g);
	res.b = fminf(255, ambient.b + diffuse.b + specular.b);
	return (res);
}
