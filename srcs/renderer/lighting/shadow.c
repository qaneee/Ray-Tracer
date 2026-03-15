/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:43:06 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:46 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_in_shadow(t_scene *s, t_vec3 p, t_vec3 light_norm, float light_dst)
{
	t_ray	shadow_ray;
	t_objs	*objs;
	float	t;

	shadow_ray.direct = light_norm;
	shadow_ray.origin = vec_add(p, vec_scale(light_norm, EPS));
	objs = s->objs;
	while (objs)
	{
		t = -1.0f;
		if (intersect_obj(&shadow_ray, objs, &t))
		{
			if (t > EPS && t < light_dst)
				return (1);
		}
		objs = objs->next;
	}
	return (0);
}
