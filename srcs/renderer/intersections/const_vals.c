/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:47:38 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:30 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_object_cache(t_objs *obj)
{
	t_vec3	axis_offset;

	if (!obj)
		return ;
	obj->radius_sq = obj->radius * obj->radius;
	obj->half_height = obj->height * 0.5f;
	obj->cone_k = 0.0f;
	obj->cap_top_center = obj->pos;
	obj->cap_bottom_center = obj->pos;
	obj->cone_base_center = obj->pos;
	if (obj->type == CYLINDER)
	{
		axis_offset = vec_scale(obj->orientation, obj->half_height);
		obj->cap_top_center = vec_add(obj->pos, axis_offset);
		obj->cap_bottom_center = vec_subt(obj->pos, axis_offset);
	}
	else if (obj->type == CONE && obj->height > EPS)
	{
		obj->cone_k = obj->radius_sq / (obj->height * obj->height);
		obj->cone_base_center = vec_add(obj->pos,
				vec_scale(obj->orientation, obj->height));
	}
}
