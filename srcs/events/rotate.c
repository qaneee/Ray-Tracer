/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:00:42 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/28 16:19:21 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_axis_from_key(int keycode, t_vec3 *axis, float *angle,
	float degrees)
{
	if (!axis || !angle)
		return (0);
	if (keycode == KEY_R)
		return (*axis = (t_vec3){1.0f, 0.0f, 0.0f}, *angle = degrees, 1);
	if (keycode == KEY_F)
		return (*axis = (t_vec3){1.0f, 0.0f, 0.0f}, *angle = -degrees, 1);
	if (keycode == KEY_T)
		return (*axis = (t_vec3){0.0f, 1.0f, 0.0f}, *angle = degrees, 1);
	if (keycode == KEY_G)
		return (*axis = (t_vec3){0.0f, 1.0f, 0.0f}, *angle = -degrees, 1);
	if (keycode == KEY_Y)
		return (*axis = (t_vec3){0.0f, 0.0f, 1.0f}, *angle = degrees, 1);
	if (keycode == KEY_H)
		return (*axis = (t_vec3){0.0f, 0.0f, 1.0f}, *angle = -degrees, 1);
	return (0);
}

static t_vec3	get_camera_right_from_dir(t_vec3 dir)
{
	t_vec3	world_up;
	t_vec3	right;

	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	dir = normal_vector(dir);
	right = cross_product(dir, world_up);
	if (vec_length(right) < 1e-6f)
		right = cross_product(dir, (t_vec3){0.0f, 0.0f, 1.0f});
	return (normal_vector(right));
}

t_vec3	rotate_axis(t_vec3 vec, t_vec3 k, float degree)
{
	float	radians;
	t_vec3	arg1;
	t_vec3	arg2;
	t_vec3	arg3;

	if (vec_length(vec) < 1e-6f || vec_length(k) < 1e-6f)
		return (vec);
	k = normal_vector(k);
	radians = degree * M_PI / 180.0f;
	arg1 = vec_scale(vec, cosf(radians));
	arg2 = vec_scale(cross_product(k, vec), sinf(radians));
	arg3 = vec_scale(k, dot_product(k, vec) * (1.0f - cosf(radians)));
	vec = vec_add(vec_add(arg1, arg2), arg3);
	return (vec);
}

int	rotate_camera_dir(t_camera *cam, int keycode, float degrees)
{
	t_vec3	axis;
	float	angle;

	if (!cam)
		return (0);
	if (!get_axis_from_key(keycode, &axis, &angle, degrees))
		return (0);
	if (keycode == KEY_R || keycode == KEY_F)
		axis = get_camera_right_from_dir(cam->dir);
	cam->dir = normal_vector(rotate_axis(cam->dir, axis, angle));
	return (1);
}

int	rotate_object(t_objs *obj, int keycode, float degrees)
{
	t_vec3	axis;
	float	angle;

	if (!obj || obj->type == SPHERE)
		return (0);
	if (!get_axis_from_key(keycode, &axis, &angle, degrees))
		return (0);
	obj->orientation = normal_vector(rotate_axis(obj->orientation, axis,
				angle));
	return (1);
}
