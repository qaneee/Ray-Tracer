/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:55:39 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/10 01:03:39 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_camera *cam, int width, int height)
{
	float	theta;
	float	viewport_height;
	float	aspect_ratio;
	t_vec3	world_up;

	aspect_ratio = (float)width / height;
	theta = fov_to_radians(cam);
	viewport_height = 2.0f * tanf(theta / 2.0f);
	cam->forward = cam->dir;
	cam->viewport_width = viewport_height * aspect_ratio;
	cam->viewport_height = viewport_height;
	cam->aspect_ratio = aspect_ratio;
	world_up = (t_vec3){0, 1, 0};
	if (cam->forward.y > 0.999f)
		world_up = (t_vec3){0, 0, 1};
	cam->right = normal_vector(cross_product(cam->forward, world_up));
	cam->up = cross_product(cam->right, cam->forward);
}

t_ray	get_camera_ray(t_camera *cam, int x, int y, t_scene *sc)
{
	t_ray	ray;
	t_vec3	pixel_pos;
	float	u;
	float	v;

	u = (2.0f * x / sc->width - 1.0f) * cam->viewport_width / 2.0f;
	v = (1.0f - 2.0f * y / sc->height) * cam->viewport_height / 2.0f;
	pixel_pos = vec_add(cam->pos, cam->forward);
	pixel_pos = vec_add(pixel_pos, vec_scale(cam->right, u));
	pixel_pos = vec_add(pixel_pos, vec_scale(cam->up, v));
	ray.origin = cam->pos;
	ray.direct = normal_vector(vec_subt(pixel_pos, cam->pos));
	return (ray);
}
