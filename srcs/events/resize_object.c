/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:48:06 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:14 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	resize_sphere(t_objs *obj, int keycode, float step)
{
	if (keycode == KEY_M)
		obj->diameter -= step;
	else if (keycode == KEY_V)
		obj->diameter += step;
	else
		return (0);
	if (obj->diameter < EPS)
		obj->diameter = EPS;
	obj->radius = obj->diameter * 0.5f;
	return (1);
}

static int	resize_cylinder(t_objs *obj, int keycode, float step)
{
	if (keycode == KEY_M)
		obj->diameter -= step;
	else if (keycode == KEY_V)
		obj->diameter += step;
	else if (keycode == KEY_I)
		obj->height += step;
	else if (keycode == KEY_K)
		obj->height -= step;
	else
		return (0);
	if (obj->diameter < EPS)
		obj->diameter = EPS;
	if (obj->height < EPS)
		obj->height = EPS;
	obj->radius = obj->diameter * 0.5f;
	return (1);
}

int	resize_object(t_objs *obj, int keycode, float step)
{
	if (!obj)
		return (0);
	if (obj->type == SPHERE)
		return (resize_sphere(obj, keycode, step));
	if (obj->type == CYLINDER)
		return (resize_cylinder(obj, keycode, step));
	return (0);
}
