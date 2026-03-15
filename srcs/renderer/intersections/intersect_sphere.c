/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 01:23:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:57:18 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_sphere(t_ray ray, t_objs *sphere, float *t)
{
	t_vec3	pos;
	float	a;
	float	b;
	float	c;
	float	t_coef;

	pos = vec_subt(ray.origin, sphere->pos);
	a = dot_product(ray.direct, ray.direct);
	b = 2 * dot_product(pos, ray.direct);
	c = dot_product(pos, pos) - sphere->radius_sq;
	t_coef = ft_quadratic(a, b, c);
	if (t_coef < EPS)
		return (0);
	*t = t_coef;
	return (1);
}
