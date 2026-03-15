/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 01:41:35 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:07 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_plane(t_ray ray, t_objs *plane, float *t)
{
	t_vec3	p0_origin;
	float	denom;
	float	nomin;

	p0_origin = vec_subt(plane->pos, ray.origin);
	nomin = dot_product(p0_origin, plane->orientation);
	denom = dot_product(ray.direct, plane->orientation);
	if (fabsf(denom) < 1e-6)
		return (0);
	*t = nomin / denom;
	if (*t < EPS)
		return (0);
	return (1);
}
