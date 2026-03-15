/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:47:24 by arvardan          #+#    #+#             */
/*   Updated: 2026/02/16 20:30:07 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	trace_ray(t_scene *sc, t_ray *ray, int depth)
{
	t_hit	hit;
	t_color	final_color;
	t_color	refl;

	if (!closest_intersection(sc, ray, &hit))
		return (get_skybox_color(sc, ray));
	final_color = combine_lighting(sc, &hit, ray->origin);
	if (depth < REFLECTION_DEPTH && hit.objs->reflection > 0.0f)
	{
		refl = get_reflect_vec(sc, &hit, ray, depth + 1);
		final_color = blend_color(final_color, refl, hit.objs->reflection);
	}
	return (final_color);
}

void	render_scene(t_data *data)
{
	t_ray	ray;
	t_color	color;
	int		x;
	int		y;

	init_camera(&data->scene.camera, data->scene.width, data->scene.height);
	y = 0;
	while (y < data->scene.height)
	{
		x = 0;
		while (x < data->scene.width)
		{
			ray = get_camera_ray(&data->scene.camera, x, y, &data->scene);
			color = trace_ray(&data->scene, &ray, 0);
			put_pixel(&data->mlx, x, y, get_color(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		data->mlx.img, 0, 0);
}
