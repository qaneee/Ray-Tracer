/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:42:54 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:31 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_obj(t_ray *ray, t_objs *obj, float *t)
{
	if (obj->type == CYLINDER)
		return (intersect_cylinder(*ray, obj, t));
	if (obj->type == CONE)
		return (intersect_cone(*ray, obj, t));
	if (obj->type == SPHERE)
		return (intersect_sphere(*ray, obj, t));
	if (obj->type == PLANE)
		return (intersect_plane(*ray, obj, t));
	return (0);
}

static int	try_update_hit(t_hit *hit, t_objs *obj, float t)
{
	if (t > EPS && t < hit->t)
	{
		hit->t = t;
		hit->objs = obj;
		return (1);
	}
	return (0);
}

int	closest_intersection(t_scene *sc, t_ray *ray, t_hit *hit)
{
	t_objs	*obj;
	int		fl_hit;
	float	t;

	obj = sc->objs;
	fl_hit = 0;
	hit->t = INFINITY;
	while (obj)
	{
		if (intersect_obj(ray, obj, &t))
			fl_hit |= try_update_hit(hit, obj, t);
		obj = obj->next;
	}
	if (fl_hit)
	{
		hit->point = vec_add(ray->origin, vec_scale(ray->direct, hit->t));
		calculate_normal(hit);
		hit->color = get_object_color(hit);
	}
	return (fl_hit);
}
