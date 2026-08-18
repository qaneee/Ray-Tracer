/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:02:15 by arvardan          #+#    #+#             */
/*   Updated: 2026/08/18 17:36:07 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cylinder_cap_normal(t_hit *hit, t_vec3 *out)
{
	float	max_dist_sq;
	t_vec3	delta;

	max_dist_sq = (hit->objs->radius + EPS) * (hit->objs->radius + EPS);
	delta = vec_subt(hit->point, hit->objs->cap_top_center);
	if (dot_product(delta, delta) < max_dist_sq)
		return ((*out = hit->objs->orientation), 1);
	delta = vec_subt(hit->point, hit->objs->cap_bottom_center);
	if (dot_product(delta, delta) < max_dist_sq)
		return ((*out = vec_scale(hit->objs->orientation, -1.0f)), 1);
	return (0);
}

int	cone_base_normal(t_hit *hit, t_vec3 *out)
{
	float	max_dist_sq;
	t_vec3	delta;

	max_dist_sq = (hit->objs->radius + EPS) * (hit->objs->radius + EPS);
	delta = vec_subt(hit->point, hit->objs->cone_base_center);
	if (dot_product(delta, delta) < max_dist_sq)
		return ((*out = hit->objs->orientation), 1);
	return (0);
}

t_vec3	cone_side_normal(t_hit *hit)
{
	t_vec3	apex_to_point;
	float	h;

	apex_to_point = vec_subt(hit->point, hit->objs->pos);
	h = dot_product(apex_to_point, hit->objs->orientation);
	return (normal_vector(vec_subt(
				vec_scale(hit->objs->orientation, h),
				vec_scale(apex_to_point, hit->objs->cone_k)
			)));
}
