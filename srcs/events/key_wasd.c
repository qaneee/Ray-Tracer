/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wasd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:45:24 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/10 00:47:47 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_camera_right(t_camera *c)
{
	t_vec3	world_up;
	t_vec3	right;

	world_up = (t_vec3){0, 1, 0};
	right = cross_product(c->dir, world_up);
	if (vec_length(right) < 1e-6f)
		right = cross_product(c->dir, (t_vec3){0, 0, 1});
	return (normal_vector(right));
}

void	move_forward(t_data *d, float step)
{
	t_camera	*c;

	c = &d->scene.camera;
	c->pos = vec_add(c->pos, vec_scale(c->dir, step));
}

void	move_backward(t_data *d, float step)
{
	t_camera	*c;

	c = &d->scene.camera;
	c->pos = vec_subt(c->pos, vec_scale(c->dir, step));
}

void	move_right(t_data *d, float step)
{
	t_camera	*c;
	t_vec3		right;

	c = &d->scene.camera;
	right = get_camera_right(c);
	c->pos = vec_add(c->pos, vec_scale(right, step));
}

void	move_left(t_data *d, float step)
{
	t_camera	*c;
	t_vec3		left;

	c = &d->scene.camera;
	left = get_camera_right(c);
	c->pos = vec_subt(c->pos, vec_scale(left, step));
}
