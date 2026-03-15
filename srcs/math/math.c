/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:43:20 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:24 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_quadratic(float a, float b, float c)
{
	float	discriminant;
	float	x0;
	float	x1;
	float	tmp;

	if (fabsf(a) < 1e-6)
		return (-1.0f);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0f)
		return (-1.0f);
	x0 = (-b + sqrtf(discriminant)) / (2 * a);
	x1 = (-b - sqrtf(discriminant)) / (2 * a);
	if (x0 > x1)
	{
		tmp = x0;
		x0 = x1;
		x1 = tmp;
	}
	if (x0 >= EPS)
		return (x0);
	if (x1 >= EPS)
		return (x1);
	return (-1.0f);
}

float	fov_to_radians(t_camera *c)
{
	return (c->fov * M_PI / 180.0);
}
